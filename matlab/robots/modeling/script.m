num_links = 3;

% Generate random arm lengths between a specific range, for example, 1.0 to 3.0
% arm_length = 1.0 + 2.0 * rand(1, num_links)';
arm_length = [2 2 2];

% Generate rand
% om initial positions, for example between 0 and 10
init_pos = 10 * rand(1, num_links)';
% Generate random amplitudes, for example between 20 and 40
amplitude = 20 + 20 * rand(1, num_links)';
% Generate random frequencies, for example between 10 and 20
freq = 10 + 10 * rand(1, num_links)';
% Generate random configurations, for example between 0 and 10
config = 10 * rand(num_links, 1);
% Generate random velocities, for example between 10 and 1100
vel = 10 + 1090 * rand(num_links, 1);
% Generate random torques, for example between 100 and 200
tq = 100 + 100 * rand(num_links, 1)';


rho = 10000000;
dt = 0.001;
radius = 0.00002;
damping_factor = 1;

joint_axes = [0 0 1;  % Axis for joint 1 (z-axis)
              1 0 0;
              0 0 1];
joint_angles = [0 pi/2 0];

acc_temp = make_scara_robot(rho, radius, arm_length,joint_axes,joint_angles,config,vel,tq);


% acc = forwardDynamics(robot,config,vel,tq');

% [joint_acc, pos_tcp] = scara_robot_2dof_FD(config, vel, rho, radius, arm_length, tq');
o = [0 0 0].';
wz = [0 0 1].';
wy = [0 1 0].';
wx = [1 0 0].';



[joint_acc_new, pos_tcp_new, cus_rob] = robot_chain_dynamics(config, vel, rho, num_links ,radius, arm_length, tq');
joint_acc_new
% err_2 = joint_acc_new - acc


% i=5;
% matlab_torque(i,:) = [10 20 30];
% acc_mat = forwardDynamics(robot,config,vel,matlab_torque(i,:)')
% [acc_cus, pos_tcp] = calcSysMatrices(config, vel, rho, radius, arm_length, matlab_torque(i,:)');
% disp(acc_cus)
%
% for i=1:length(matlab_torque)
%     acc = forwardDynamics(robot,config,vel,matlab_torque(i,:)');
%     vel = vel + acc*dt;
%     config = config + vel*dt;
%
%     fd_acc(i,:) = acc;
% end
