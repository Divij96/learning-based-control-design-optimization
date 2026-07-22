function ROBOT = Planar2DoF(rho, radius, arm_length)
% Planar2DoF Description.
%   Planar manipulator with 2 DoF.
%   ...

% Origin of the frames and axis
E = eye(3);
o = [0 0 0].';
wz = [0 0 1].';

% Initial origins of joint coordinate systems represented in global
% coordinate system (one for each column)
jointOrigins = [
    0, arm_length(1)
    0, 0
    0, 0];

% Parameter of end-effector
TCP_T_EE = [E, [arm_length(1) 0 0]'; o.', 1]; % homogeneous transformation of tcp

% Mass, Center of Mass, and Inertia calculations for each link
Mass = cell(2,1);
g0 = cell(2,1);
for iLink = 1:2
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

% Relative body jacobians adjusted for 2 DOF planar robot (rotation around z-axis)
ROBOT.csi = repmat([o; wz], 2, 1)

% Gravitational acceleration constant
ROBOT.g_vec = [0 0 0]';

% Pack into ROBOT structure
% ROBOT.g0 = cell2mat(g0);
% ROBOT.Mass = cell2mat(Mass);
ROBOT.g0 = [g0{1}; g0{2}];
ROBOT.Mass = [Mass{1}; Mass{2}];

ROBOT.tcp_t_ee = TCP_T_EE

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
