function acc = forward_dynamics_robot_4arm(rho, radius, arm_length, joint_axes, joint_angles, config, vel, tq)
    % Validate inputs
    validateattributes(arm_length, {'numeric'}, {'positive', 'vector'});
    validateattributes(radius, {'numeric'}, {'positive', 'scalar'});
    validateattributes(joint_axes, {'numeric'}, {'size', [length(arm_length), 3]});
    numLinks = 4;
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
            jointTransform = trvec2tform([sum(arm_length(1:i-1)) 0 0]) * axang2tform([joint_axes(i, :) joint_angles(i)]);
        end
        setFixedTransform(joint, jointTransform);

        % Generate body name
        bodyName = blanks(6); % Pre-allocate with blanks
        bodyName(1:6) = sprintf('link%02d', int32(i));

        % Create and configure body
        bodies{i} = createBody(bodyName, joint, radius, arm_length(i), rho);

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

    robot.Gravity = [0 0 -9.81];
    % Perform forward dynamics
    acc = forwardDynamics(robot, config, vel, tq');
end

function body = createBody(bodyName, joint, radius, length, rho)
    % Create a rigid body with the specified parameters
    body = robotics.RigidBody(bodyName, 'MaxNumCollisions', 10);
    body.Joint = joint;

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
