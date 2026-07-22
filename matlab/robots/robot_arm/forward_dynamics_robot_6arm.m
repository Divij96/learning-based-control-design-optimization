function [acc, linkPositionsArray] = forward_dynamics_robot_6arm(rho, radius, arm_length, joint_axes, joint_angles, config, vel, tq)
    % Validate inputs
    validateattributes(arm_length, {'numeric'}, {'positive', 'vector'});
    validateattributes(radius, {'numeric'}, {'positive', 'scalar'});
    validateattributes(joint_axes, {'numeric'}, {'size', [length(arm_length), 3]});
    numLinks = 6;
    % Create a robot model
    robot = robotics.RigidBodyTree('DataFormat', 'column', 'MaxNumBodies', numLinks + 1);

    % Pre-allocate rigid bodies
    bodies = cell(1, numLinks);

    % Configure the bodies
    for i = 1:numLinks
        % Create joint and link
        jointName = sprintf('jnt%d', int8(i));
        joint = robotics.Joint(jointName, 'revolute');

        % Set the joint's transformation
        if i == 1
            jointTransform = trvec2tform([0 0 0]) * axang2tform([joint_axes(i, :) 0]);
        else
            jointTransform = trvec2tform([arm_length(i) 0 0]) * axang2tform([joint_axes(i, :) joint_angles(i)]);
        end
        setFixedTransform(joint, jointTransform);

        % Generate body name
        bodyName = blanks(6); % Pre-allocate with blanks
        bodyName(1:6) = sprintf('link%02d', int32(i));

        % Create and configure body
        bodies{i} = createBody(bodyName, joint, joint_axes(i, :),radius, arm_length(i), rho);

    end

    % Add bodies to the robot model
    addBody(robot, bodies{1}, 'base');
    prevBodyName = blanks(6); % Pre-allocate with blanks

    prevBodyName(1:6) = sprintf('link%02d', int32(1));
    addBody(robot, bodies{2}, prevBodyName);
    prevBodyName(1:6) = sprintf('link%02d', int32(2));
    addBody(robot, bodies{3}, prevBodyName);
    prevBodyName(1:6) = sprintf('link%02d', int32(3));
    addBody(robot, bodies{4}, prevBodyName);
    prevBodyName(1:6) = sprintf('link%02d', int32(4));
    addBody(robot, bodies{5}, prevBodyName);
    prevBodyName(1:6) = sprintf('link%02d', int32(5));
    addBody(robot, bodies{6}, prevBodyName);

    % Assuming 'robot' is your RigidBodyTree object and bodies{6} is the last link

    % Create the end effector as a rigid body
    body_EE = robotics.RigidBody('end_effector');

    % Create a fixed joint to attach the end effector to the last link
    joint_EE = robotics.Joint('end_effector_joint', 'fixed');

    % Define the transformation from the last link to the end effector
    % This transformation positions the end effector relative to the last link.
    % Adjust [0, 0, 0] to position the end effector as needed.
    setFixedTransform(joint_EE, trvec2tform([arm_length(6), 0, 0])); % Example transformation

    % Associate the joint with the end effector
    body_EE.Joint = joint_EE;
    prevBodyName(1:6) = sprintf('link%02d', int32(6));

    % Add the end effector to the robot, attaching it to the last link
    addBody(robot, body_EE, prevBodyName);

    robot.Gravity = [0 0 -9.81];
    % Perform forward dynamics
    acc = forwardDynamics(robot, config, vel, tq');

    % Initialize link positions array
    linkPositionsArray = zeros(numLinks, 3); % Each row: [startX, startY, startZ, endX, endY, endZ]

    endTransformMatrix = getTransform(robot, config, sprintf('link%02d', 2));
    linkPositionsArray(1, :) = endTransformMatrix(1:3, 4)';
    endTransformMatrix = getTransform(robot, config, sprintf('link%02d', 3));
    linkPositionsArray(2, :) = endTransformMatrix(1:3, 4)';
    endTransformMatrix = getTransform(robot, config, sprintf('link%02d', 4));
    linkPositionsArray(3, :) = endTransformMatrix(1:3, 4)';
    endTransformMatrix = getTransform(robot, config, sprintf('link%02d', 5));
    linkPositionsArray(4, :) = endTransformMatrix(1:3, 4)';
    endTransformMatrix = getTransform(robot, config, sprintf('link%02d', 6));
    linkPositionsArray(5, :) = endTransformMatrix(1:3, 4)';
    endTransformMatrix = getTransform(robot, config, 'end_effector');
    linkPositionsArray(6, :) = endTransformMatrix(1:3, 4)';

end

function body = createBody(bodyName, joint, joint_axes,radius, length, rho)
    % Create a rigid body with the specified parameters
    body = robotics.RigidBody(bodyName, 'MaxNumCollisions', 10);
    body.Joint = joint;
    body.Joint.JointAxis = joint_axes;
    % Set collision geometry
    collisionObj = collisionCylinder(radius, length);
    collisionObj.Pose = [axang2rotm([0 1 0 pi/2]), [length/2; 0; 0]; 0 0 0 1];
    body.addCollision(collisionObj);
    % Compute dynamics based on cylindrical geometry
    m = pi * radius^2 * length * rho; % Mass
    com = [length/2, 0, 0]; % Center of mass
    Ix = 0.5 * m * radius^2; % Inertia around x-axis
    Iz = (1/4) * m * radius^2 + (1/12) * m * length^2; % Inertia around x and y axis
    Iz = Iz + m * (length/2)^2; % Adjust inertia for the frame origin
    body.Mass = m;
    body.CenterOfMass = com;
    body.Inertia = [Ix, Iz, Iz, 0, 0, 0];
end
