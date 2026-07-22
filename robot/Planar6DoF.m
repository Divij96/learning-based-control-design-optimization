function ROBOT = Planar6DoF(m_fac, m_EE, com_EE, I_EE)
%Planar6DoF  Description.
%   Planar manipulator with 6 DoF.
%   load mass: m_EE
%   mass factor: mfac
% Output:
% ROBOT:    Robot parameters, MATLAB structure with five fields (see [1]):
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
% References:
% [1] Garofalo, Gianluca, Christian Ott and Alin Albu-Schaeffer. "On the
% closed form computation of the dynamic matrices and their differentiations."
% 2013 IEEE/RSJ International Conference on Intelligent Robots and Systems
% (2013): 2364-2359.

% Origin of the frames and axis
E = eye(3);
o = [0 0 0].';
wx = [1 0 0].';
wy = [0 1 0].';

% Initial origins of joint coordinate systems represented in global
% coordinate system (one for each column)
jointOrigins = [
    0       0       0       0       0       0
    0       0       0       0       0       0
    0       0.25    0.5     0.5     0.5     0.5];

% Parameter of end-effektor
TCP_T_EE = [E, [0 0 0.5]';o.', 1]; % homogeneous transformation of tcp

% Mass of the links
m = [1.0 1.0 1.0 1.0 1.0 1.0] * m_fac;

% CoM in the link frame (one for each row)
com = [0, 0, 0.125;
    0, 0, 0.25;
    0, 0, 0.25;
    0, 0, 0.25;
    0, 0, 0.25;
    0, 0, 0.25];
com(end, :) = ( m_EE * com_EE + m(end) * com(end, :) ) ./ ( m(end) + m_EE );
m(end) = m(end) + m_EE;

% Inertia tensor with respect to the CoM in the link frame
I = repmat({zeros(3,3)}, 6, 1);
I{end} = I{end} + I_EE;

% Compute constant body inertia matrix (Mass) and initial relative homogeneous
% transformation matrix (g0)
Mass = cell(6,1);
g0 = cell(6,1);
for iLink = 1:6
    Mass{iLink} = Inertia(m(iLink),com(iLink,:),I{iLink});
    g0{iLink} = [E, jointOrigins(:,iLink); o.', 1];
end

%-------------------------------------------------------------------------%
ROBOT.g0 = cell2mat(g0);
ROBOT.Mass = cell2mat(Mass);

% Relative body jacobians
% The first three elements correspond to the relative linear velocity
% The last three elements correspond to the relative angular velocity
ROBOT.csi = [ ...
    [wy; o]; ...
    [o; wx]; ...
    [o; wx]; ...
    [o; wx]; ...
    [o; wx]; ...
    [o; wx]];

ROBOT.tcp_t_ee = TCP_T_EE;

% Gravitational acceleration constant
ROBOT.g_vec = [0 0 9.81]';
end

% utility functions -------------------------------------------------------%
function out = Skew(vec)
%Skew  Skew symmetric matrix.
%   out=Skew(vec) calculates the skew symmetric matrix of a 3D vector.

out = [
    0         -vec(3)   vec(2)
    vec(3)    0         -vec(1)
    -vec(2)   vec(1)    0
    ];

end

function out = Inertia(m, c, I)
%   Inertia  Spatial rigid-body inertia from mass, CoM and rotational inertia.
%   M=Inertia(m,c,I) calculates the spatial inertia matrix of a rigid
%   body from its mass, centre of mass (3D vector) and rotational inertia
%   (3x3 matrix) about the origin of its own body frame.

S = Skew(c);
out = [
    m*eye(3)    -m*S
    m*S         I-m*S*S
    ];

end