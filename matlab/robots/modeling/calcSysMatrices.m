%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculation of system matrices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Calculates the dynamic and kinematic matrices by using the iterative
% algorithm proposed in [1]. Kinematic and inertia parameters of the robot
% can be given in a compact way. Additionally, this algorithm can ensure
% the skew-symmetric property of dM - 2C.
%
% Inputs:
% q:        Current joint positions, n-by-1 vector
% dq:       Current joint velocities, n-by-1 vector
% ROBOT:    Robot parameters, MATLAB structure with three
%           fields:
%           g0:       4n-by-4 matrix stacking vertically the homogeneous
%                     transformation matrices from parent to link in the
%                     zero-configuration
%           csi:      6n-by-1 vector stacking vertically the 6-by-1
%                     relative body jacobian (twist)
%           Mass:     6n-by-6 matrix stacking vertically the 6-by-6
%                     constant body inertia matrix from parent to link
%           g_vec:    3-by-1 gravitational acceleration constant
%           tcp_t_ee: 4-by-4 homogeneous transformation matrix from
%                     end-effector to tcp
%
% Outputs
% M:        n-by-n joint space inertia matrix
% CC:       n-by-n joint space Cor./centrifugal matrix
% g:        n-by-1 gravity torque vector
% O_J_TCP:  6-by-n hybrid jacobian of tcp
% B_J_TCP:  6-by-n body jacobian of tcp
% Htm_TCP:  4-by-4 homogeneous transformation matrix from tcp to base
%
% References
% [1] Garofalo, Gianluca, Christian Ott and Alin Albu-Schäffer. "On the
% closed form computation of the dynamic matrices and their differentiations."
% 2013 IEEE/RSJ International Conference on Intelligent Robots and Systems
% (2013): 2364-2359.
%
% Implemented by Xuwei Wu.

function [joint_acc, pos_tcp] = calcSysMatrices(q, dq, rho, radius, arm_length, torque)
%#codegen
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ROBOT = Planar3DoF(rho, radius, arm_length);

% reshape signals
ndof = size(ROBOT.g0, 1)/4;
q = reshape(q, ndof, 1);
dq = reshape(dq, ndof, 1);

% pre-allocate memory for variables
M = zeros(ndof, ndof);
dM = zeros(ndof, ndof);
CC = zeros(ndof, ndof);
g = zeros(ndof, 1);
J_pre = zeros(6, ndof);
dJ_pre = zeros(6, ndof);
inertialTwist_pre = zeros(6,1);
O_Htm_pre = eye(4);

% iterate from the root to the end-effector of the serial manipulator
for iLink = 1:ndof

    % initialize indices of the current iteration
    idxStart_4Row = 4*(iLink-1) + 1;
    idxEnd_4Row = idxStart_4Row + 3;
    idxStart_6Row = 6*(iLink-1) + 1;
    idxEnd_6Row = idxStart_6Row + 5;

    % compute relative body twist
    relBodyJac = ROBOT.csi(idxStart_6Row:idxEnd_6Row);
    relBodyJac = reshape(relBodyJac, 6, 1);
    relTwist = relBodyJac * dq(iLink);

    % compute relative homogeneous transformation matrix between link and
    % its parent
    Htm = ROBOT.g0(idxStart_4Row:idxEnd_4Row, 1:4);
    Htm = Htm * Exponential(relBodyJac, q(iLink));

    % propagate rotation matrix, body twists, body jacobians and
    % derivatives of body jacobians
    O_Htm = O_Htm_pre * Htm;
    inertialTwist = relTwist;
    invAd = InvAdjoint(Htm);
    J = zeros(6, ndof);
    dJ = zeros(6, ndof);
    if iLink > 1
        inertialTwist = inertialTwist + invAd * inertialTwist_pre;
        J(1:6, 1:iLink-1) = invAd * J_pre(1:6, 1:iLink-1);
        dJ(1:6, 1:iLink-1) = invAd * dJ_pre(1:6, 1:iLink-1)- LieBracket(relTwist) * J(1:6, 1:iLink-1);
    end
    J(1:6, iLink) = relBodyJac;

    % update inertia matrix
    tmp = J(1:6, 1:iLink)' * ROBOT.Mass(idxStart_6Row:idxEnd_6Row, 1:6);
    M(1:iLink, 1:iLink) = M(1:iLink, 1:iLink) + tmp * J(1:6, 1:iLink);
    tmptmp = tmp * dJ(1:6, 1:iLink);
    dM(1:iLink, 1:iLink) = dM(1:iLink, 1:iLink) + tmptmp + tmptmp';

    % update Cor.\centrifugal matrix
    % Method 1: Original version from [1]
    % Mass_x_ad_tmp = ROBOT.Mass(idxStart_6Row:idxEnd_6Row, 1:6) * LieBracket(inertialTwist);
    % Mass_x_ad_tmp = Mass_x_ad_tmp - Mass_x_ad_tmp';
    Mass_x_ad_tmp = SkewCoriolis(ROBOT.Mass(idxStart_6Row:idxEnd_6Row, 1:6), inertialTwist(4:6));
    CC(1:iLink, 1:iLink) = CC(1:iLink, 1:iLink) + J(1:6, 1:iLink)' * Mass_x_ad_tmp * J(1:6, 1:iLink) + tmp * dJ(1:6, 1:iLink);

    % update gravity torque vector
    g(1:iLink) = g(1:iLink) + tmp(1:iLink, 1:3) * O_Htm(1:3, 1:3)' * ROBOT.g_vec;

    % update variables of parent link
    J_pre = J;
    dJ_pre = dJ;
    inertialTwist_pre = inertialTwist;
    O_Htm_pre = O_Htm;

end
Htm_TCP = O_Htm(1:4,1:4) * ROBOT.tcp_t_ee;
pos_tcp = Htm_TCP(1:3,4);
B_J_TCP = InvAdjoint(ROBOT.tcp_t_ee) * J(1:6, 1:ndof);
O_J_TCP = [Htm_TCP(1:3, 1:3)* B_J_TCP(1:3, 1:ndof);Htm_TCP(1:3, 1:3)*B_J_TCP(4:6, 1:ndof)];
joint_acc = M\(-CC*dq + torque - g);

end

function out = Skew(vec)
% Skew operator
% Implemented by Gianluca Garofalo.

out = [
    0         -vec(3)   vec(2)
    vec(3)    0         -vec(1)
    -vec(2)   vec(1)    0
    ];

end

function out = SkewCoriolis(Mass, w)
Sw = Skew(w);
tmp = Mass(4:6, 1:3)*Sw;
tmp2 = Mass(4:6, 4:6)*Sw;
out = [Mass(1,1)*Sw -tmp'; tmp tmp2 - tmp2'];
end

function out = Exponential(csi, theta)
% Twist exponential of the relative body jacobian
% Implemented by Gianluca Garofalo.

o = [0 0 0].';
I = eye( 3 );
v = csi(1:3);
w = csi(4:6);
if all( w == o )
    out = [I v*theta; zeros(1,3) 1];
else
    w_hat = Skew( w );
    R_minus_I = w_hat * sin( theta ) + w_hat * w_hat * ( 1 - cos(theta) );
    out = [I+R_minus_I zeros(3,1); zeros(1,3) 1];
end
end

function out = InvAdjoint(Htm)
% Inverse of the adjoint transformation
% Implemented by Gianluca Garofalo.

R_tra = Htm(1:3,1:3).';
p_hat = Skew( Htm(1:3,4) );
out = [R_tra -R_tra*p_hat; zeros(3) R_tra];
end

function ad = LieBracket(twist)
% Lie bracket of the body twist
% Implemented by Gianluca Garofalo.

Sv = Skew( twist(1:3) );
Sw = Skew( twist(4:6) );
ad = [Sw Sv; zeros(3) Sw];
end

% utility functions -------------------------------------------------------%
function out = Inertia(m, c, I)
% Inertia  Spatial rigid-body inertia from mass, CoM, and rotational inertia.
% ...
    S = Skew(c);
    out = [
        m*eye(3),   -m*S
        m*S,        I - m*S*S
    ];
end

function ROBOT = Planar3DoF(rho, radius, arm_length)
% Planar3DoF Description.
%   Planar manipulator with 3 DoF.
%   ...

% Origin of the frames and axis
E = eye(3);
o = [0 0 0].';
wz = [0 0 1].';

% Initial origins of joint coordinate systems represented in global
% coordinate system (one for each column)
jointOrigins = [
    0, arm_length(1), arm_length(2)
    0, 0, 0
    0, 0, 0];

% Parameter of end-effector
TCP_T_EE = [E, [arm_length(3) 0 0]'; o.', 1]; % homogeneous transformation of tcp

% Mass, Center of Mass, and Inertia calculations for each link
Mass = cell(3,1);
g0 = cell(3,1);
for iLink = 1:3
    % Compute dynamics based on cylindrical geometry
    m = pi * radius^2 * arm_length(iLink) * rho; % Mass
    com = [arm_length(iLink)/2, 0, 0]; % Center of mass
    Ix = 0.5 * m * radius^2; % Inertia around z-axis
    Iz = (1/4) * m * radius^2 + (1/12) * m * arm_length(iLink)^2; % Inertia around x and y axis

    % Assign computed values to body
    body.Mass = m;
    body.CenterOfMass = com;
    body.Inertia = [Ix, Iz, Iz, 0, 0, 0];

    % Spatial inertia matrix
    Mass{iLink} = Inertia(body.Mass, body.CenterOfMass, diag(body.Inertia(1:3)));

    % Initial relative homogeneous transformation matrix
    g0{iLink} = [E, jointOrigins(:,iLink); o.', 1];
end

% Relative body jacobians adjusted for 3 DOF planar robot (rotation around z-axis)
ROBOT.csi = repmat([o; wz], 3, 1);

% Gravitational acceleration constant
ROBOT.g_vec = [0 0 -9.81]';

% Pack into ROBOT structure
% ROBOT.g0 = cell2mat(g0);
% ROBOT.Mass = cell2mat(Mass);
ROBOT.g0 = [g0{1}; g0{2}; g0{3}];
ROBOT.Mass = [Mass{1}; Mass{2}; Mass{3}];

ROBOT.tcp_t_ee = TCP_T_EE;

% utility functions -------------------------------------------------------%
function out = Inertia(m, c, I)
% Inertia  Spatial rigid-body inertia from mass, CoM, and rotational inertia.
% ...
    S = Skew(c);
    out = [
        m*eye(3),   -m*S
        m*S,        I - m*S*S
    ];
end

function out = Skew(vec)
% Skew symmetric matrix.
% ...
    out = [
        0,         -vec(3),   vec(2)
        vec(3),    0,         -vec(1)
        -vec(2),   vec(1),    0
    ];
end

end
