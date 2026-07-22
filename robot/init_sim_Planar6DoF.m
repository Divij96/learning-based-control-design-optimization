t_end = 5;
Ts = 1e-3;
dq0 = zeros(6,1);
q0 = [0, [45 -45 -45 -45 -45]*pi/180]';
q0_offset = [-0.2, [10 10 10 10 10]*pi/180]';

% Prepare robot parameters for online computing of robot dynamics
m_fac = 1;
m_EE = 0.0;
com_EE = 0.0;
I_EE = zeros(3,3);
ROBOT = Planar6DoF(m_fac, m_EE, com_EE, I_EE);

% Initialize visualization
if ~exist('viz', 'var') || ~isvalid(viz.figObj)
    viz = PlanarManipulatorViz(ROBOT.g0, ROBOT.csi, ROBOT.tcp_t_ee, q0);
else
    viz.updateInitJointPos(q0);
end

% Check if M is symmetric positive definite
M = calcSysMatrices(q0, dq0, ROBOT);
[~, p] = chol(M);
if p > 0
    error('Mass matrix is not positive definit.')
end

% Motor dynamics parameters
B_theta = diag(0.8*ones(1,6));
K_theta = diag(15000*ones(1,6));
D_theta = diag(0.002*ones(1,6));

% Joint impedance
K_JointImp = diag(300*ones(1,6));
%D_JointImp = diag([50, 50, 15, 10, 10, 3]);
[Vc, Lambda] = eig(K_JointImp, M);
lambda = real(diag(Lambda));
V = real(Vc);
damping_ratio = 0.7;
D_JointImp = M*V*diag(2*sqrt(lambda)*damping_ratio)/V;

% Desired inertia matrix for computed torque
M_des = M;
%M_des = diag(diag(M));

% Gains for robust controller
% K = diag([50, 50, 15, 10, 10, 3]);
K = D_JointImp;
Omega = diag(diag(K_JointImp) ./ diag(K));