function acc = test_func(rho, radius, arm_length, joint_axes, joint_angles, config, vel, tq)
    % Validate inputs
    validateattributes(arm_length, {'numeric'}, {'positive', 'vector'});
    validateattributes(radius, {'numeric'}, {'positive', 'scalar'});
    validateattributes(joint_axes, {'numeric'}, {'size', [length(arm_length), 3]});

    % Create a robot model
    numLinks = length(arm_length);
    robot = robotics.RigidBodyTree('DataFormat', 'column', 'MaxNumBodies', numLinks + 1);

    % Add bodies to the robot model in a way that's compatible with code generation
    addBodiesToRobot(robot, numLinks, arm_length, joint_axes, joint_angles, radius, rho);

    robot.Gravity = [0 0 -9.81];
    % Perform forward dynamics
    acc = forwardDynamics(robot, config, vel, tq');
end

function addBodiesToRobot(robot, numLinks, arm_length, joint_axes, joint_angles, radius, rho)
    for i = 1:numLinks
        % Create joint and link
        jointName = sprintf('jnt%d', int32(i)); % Explicit conversion to int32
        joint = robotics.Joint(jointName, 'revolute');

        % Set the joint's transformation
        if i == 1
            jointTransform = trvec2tform([0 0 0]) * axang2tform([joint_axes(i, :) 0]);
        else
            jointTransform = trvec2tform([sum(arm_length(1:i-1)) 0 0]) * axang2tform([joint_axes(i, :) joint_angles(i)]);
        end
        joint.setFixedTransform(jointTransform); % Corrected usage

        % Generate body name
        bodyName = sprintf('link%02d', int32(i));

        % Create body and configure its properties
        body = robotics.RigidBody(bodyName);
        body.Joint = joint;
        setBodyProperties(body, radius, arm_length(i), rho);

        % Add body to robot
        if i == 1
            addBody(robot, body, 'base');
        else
            prevBodyName = sprintf('link%02d', int32(i-1));
            addBody(robot, body, prevBodyName);
        end
    end
end


function setBodyProperties(body, radius, length, rho)
    % Set collision geometry
    collisionObj = collisionCylinder(radius, length);
    collisionObj.Pose = [axang2rotm([0 1 0 pi/2]), [length/2; 0; 0]; 0 0 0 1];
    body.addCollision(collisionObj);

    % Compute dynamics based on cylindrical geometry
    m = pi * radius^2 * length * rho; % Mass
    com = [length/2, 0, 0]; % Center of mass
    Ix = 0.5 * m * radius^2; % Inertia around x-axis
    Iz = (1/4) * m * radius^2 + (1/12) * m * length^2; % Inertia around z-axis
    body.Mass = m;
    body.CenterOfMass = com;
    body.Inertia = [Ix, Iz, Iz, 0, 0, 0];
end
