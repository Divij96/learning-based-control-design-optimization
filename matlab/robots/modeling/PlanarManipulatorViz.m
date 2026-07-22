classdef PlanarManipulatorViz < handle

    %% constant properties
    properties (Constant)
        FIG_NAME = 'Planar Manipulator Visualization';
        FIG_POSITION = struct( ...
            'Small', [50 50 768 680], ...
            'Normal',[50 50 984 860], ...
            'Large', [50 50 1200 1040]);
        CONTROLLER = struct( ...
            'PD', 'PD', ...
            'AugPD', 'Augmented PD', ...
            'CompTorq', 'Computed Torque', ...
            'Robust', 'Robust Controller');
    end

    %% public properties
    properties (Dependent)
        AxesWidth
        AxesHeight
    end

    properties (SetAccess = private)
        g0
        csi
        tcp_t_ee

        figObj
        figPos
        axesHandleArray
        actManipStructArray
        refManipStructArray
    end

    methods
        function axesWidth = get.AxesWidth(obj)
            axesWidth = (obj.figObj.Position(3) - 20 - 50*2)/2;
        end

        function axesHeight = get.AxesHeight(obj)
            axesHeight = (obj.figObj.Position(4) - 20*2 - 50*2)/2;
        end
    end

    %% constuctor
    methods
        function obj = PlanarManipulatorViz(g0, csi, tcp_t_ee, q0)
            obj.g0 = g0;
            obj.csi = csi;
            obj.tcp_t_ee = tcp_t_ee;
            obj.figPos = PlanarManipulatorViz.FIG_POSITION.Large;
            obj.initialization(q0);
        end

        function delete(obj)
            delete(obj.figObj)
        end
    end

    %% public methods
    methods

        function updateInitJointPos(obj, q0)
            controllerNames = fieldnames(obj.CONTROLLER);
            [p0_JointCenter, phi0] = obj.calcCartPosOfJointCenter(q0);
            initTime = 0;
            for iCtrl = 1:numel(controllerNames)
                obj.updateSingleManipulator(p0_JointCenter, phi0, initTime, obj.actManipStructArray(iCtrl))
                obj.updateSingleManipulator(p0_JointCenter, phi0, initTime, obj.refManipStructArray(iCtrl))
            end

            drawnow
        end

        function runVisualization(obj, tout, res)

            controllerNames = fieldnames(obj.CONTROLLER);
            varNames =  strcat('q_', controllerNames);
            if ~any(isfield(res, varNames))
                fprintf('No simulation results.\n')
            end
            idxResIsAvail = find(isfield(res, varNames));

            for iTs = 1:length(tout)
                if ~isvalid(obj.figObj)
                    fprintf('Visualization closed.\n')
                    return
                end
                [p_JointCenter_des, phi_des] = obj.calcCartPosOfJointCenter(res.q_des(iTs,:));

                for iCtrl = 1:length(idxResIsAvail)
                    controllerIdx = idxResIsAvail(iCtrl);
                    [p_JointCenter, phi] = obj.calcCartPosOfJointCenter(res.(varNames{controllerIdx})(iTs,:));
                    obj.updateSingleManipulator(p_JointCenter, phi, tout(iTs), obj.actManipStructArray(controllerIdx))
                    obj.updateSingleManipulator(p_JointCenter_des, phi_des, tout(iTs), obj.refManipStructArray(controllerIdx))
                end
                drawnow
            end
        end

    end

    %% private methods

    methods (Access = private)

        function initialization(obj, q0)
            obj.initFigure();
            obj.initAxes();
            obj.initManipulators(q0);
        end

        function initFigure(obj)

            obj.figObj = figure(...
                'Units',           'pixel',...
                'Position',        obj.figPos,...
                'Name',            obj.FIG_NAME,...
                'NumberTitle',     'off',...
                'IntegerHandle',   'off',...
                'HandleVisibility','callback',...
                'Resize',          'off');
        end

        function initAxes(obj)
            axesWidth = obj.AxesWidth;
            axesHeight = obj.AxesHeight;
            axesPosition = [...
                50 axesHeight+2*50+20 axesWidth axesHeight;
                axesWidth+2*50 axesHeight+2*50+20 axesWidth axesHeight;
                50 50 axesWidth axesHeight;
                axesWidth+2*50 50 axesWidth axesHeight];

            controllerNames = fieldnames(obj.CONTROLLER);
            obj.axesHandleArray = cell(numel(controllerNames), 1);
            for iCtrl = 1:numel(controllerNames)
                obj.axesHandleArray{iCtrl} = axes(...
                    'Parent',       obj.figObj,...
                    'Units',        'pixel',...
                    'Position',     axesPosition(iCtrl, :),...
                    'CLim',         [1 64], ...
                    'Xlim',         [-1.5 1.5],...
                    'Ylim',         [0 2.5],...
                    'XMinorGrid',   'on',...
                    'YMinorGrid',   'on',...
                    'Visible',      'on', ...
                    'Box',          'on');
                xlabel(obj.axesHandleArray{iCtrl} ,'Y [m]');
                ylabel(obj.axesHandleArray{iCtrl},'Z [m]');
                title(obj.axesHandleArray{iCtrl}, obj.CONTROLLER.(controllerNames{iCtrl}));
            end
        end

        function initManipulators(obj, q0)
            controllerNames = fieldnames(obj.CONTROLLER);
            emptyManipStruct = struct( ...
                'links', {}, ...
                'joints', {}, ...
                'tcpBase', {}, ...
                'tcpLeftGripper', {}, ...
                'tcpRightGripper', {}, ...
                'tcp', {}, ...
                'timeField', {});

            obj.actManipStructArray = emptyManipStruct;
            obj.refManipStructArray = rmfield(emptyManipStruct, 'timeField');
            [p0_JointCenter, phi0] = obj.calcCartPosOfJointCenter(q0);
            for iCtrl = 1:numel(controllerNames)
                [obj.actManipStructArray(iCtrl), obj.refManipStructArray(iCtrl)] = obj.initSingleManipulator(p0_JointCenter, phi0, iCtrl);
            end

            drawnow
        end

        function [actManipStruct, refManipStruct] = initSingleManipulator(obj, p_JointCenter, phi, controllerIdx)
            initTime = 0.0;
            linkWidth = 0.030;
            linkXOffset = linkWidth*cos(phi);
            linkXOffset(1) = 8*linkXOffset(1);
            linkYOffset = linkWidth*sin(phi);
            p_JointCenter(2,1) = p_JointCenter(2,1) + 0.045;
            [sphereXOffset, sphereYOffset] = sphere(20);
            sphereXOffset = 0.045*sphereXOffset;
            sphereYOffset = 0.045*sphereYOffset;
            axesHandle = obj.axesHandleArray{controllerIdx};

            links = nan(6,1);
            for iLink = 1:numel(links)
                currLinkXOffset = linkXOffset(iLink);
                currLinkYOffset = linkYOffset(iLink);
                XData = [...
                    p_JointCenter(1,iLink+1)-currLinkXOffset, p_JointCenter(1,iLink+1)+currLinkXOffset;
                    p_JointCenter(1,iLink)-currLinkXOffset,   p_JointCenter(1,iLink)+currLinkXOffset];
                YData = [...
                    p_JointCenter(2,iLink+1)-currLinkYOffset, p_JointCenter(2,iLink+1)+currLinkYOffset;
                    p_JointCenter(2,iLink)-currLinkYOffset,   p_JointCenter(2,iLink)+currLinkYOffset];

                links(iLink) = surface(...
                    'Parent',    axesHandle,...
                    'XData',     XData,...
                    'YData',     YData,...
                    'ZData',     zeros(2),...
                    'FaceColor', [0 0.4470 0.7410], ...
                    'EdgeColor', 'none');
            end

            joints = nan(6,1);
            for iJoint = 1:numel(joints)
                if iJoint > 1
                    XData = ones(21)*p_JointCenter(1,iJoint)+sphereXOffset;
                    YData = ones(21)*p_JointCenter(2,iJoint)+sphereYOffset;
                    ZData = zeros(21);
                else
                    XData = p_JointCenter(1,1) + 1.5 .* [-linkXOffset(1), linkXOffset(1);-linkXOffset(1), linkXOffset(1)];
                    YData = p_JointCenter(2,1) + [0, 0;-0.045, -0.045];
                    ZData = zeros(2);
                end

                joints(iJoint) = surface(...
                    'Parent',    axesHandle,...
                    'XData',     XData,...
                    'YData',     YData,...
                    'ZData',     ZData,...
                    'FaceColor', [0.3010 0.7450 0.9330], ...
                    'EdgeColor', 'none');
            end

            tcpBase = surface(...
                'Parent',   axesHandle,...
                'XData',    [...
                p_JointCenter(1,8)-5*linkXOffset(6) p_JointCenter(1,8)+5*linkXOffset(6);
                p_JointCenter(1,7)-5*linkXOffset(6) p_JointCenter(1,7)+5*linkXOffset(6)],...
                'YData',    [...
                p_JointCenter(2,8)-5*linkYOffset(6) p_JointCenter(2,8)+5*linkYOffset(6);
                p_JointCenter(2,7)-5*linkYOffset(6) p_JointCenter(2,7)+5*linkYOffset(6)],...
                'ZData',    zeros(2),...
                'FaceColor', [0 0.4470 0.7410], ...
                'EdgeColor', 'none');
            tcpLeftGripper = surface(...
                'Parent',   axesHandle,...
                'XData',    [...
                p_JointCenter(1,9)-3.5*linkXOffset(6) p_JointCenter(1,9)-2.0*linkXOffset(6);
                p_JointCenter(1,8)-3.5*linkXOffset(6) p_JointCenter(1,8)-2.0*linkXOffset(6)],...
                'YData',    [...
                p_JointCenter(2,9)-3.5*linkYOffset(6) p_JointCenter(2,9)-2.0*linkYOffset(6);
                p_JointCenter(2,8)-3.5*linkYOffset(6) p_JointCenter(2,8)-2.0*linkYOffset(6)],...
                'ZData',    zeros(2),...
                'FaceColor', [0 0.4470 0.7410], ...
                'EdgeColor', 'none');
            tcpRightGripper = surface(...
                'Parent',   axesHandle,...
                'XData',    [...
                p_JointCenter(1,9)+2.0*linkXOffset(6) p_JointCenter(1,9)+3.5*linkXOffset(6);
                p_JointCenter(1,8)+2.0*linkXOffset(6) p_JointCenter(1,8)+3.5*linkXOffset(6)],...
                'YData',    [...
                p_JointCenter(2,9)+2.0*linkYOffset(6) p_JointCenter(2,9)+3.5*linkYOffset(6);
                p_JointCenter(2,8)+2.0*linkYOffset(6) p_JointCenter(2,8)+3.5*linkYOffset(6)],...
                'ZData',    zeros(2),...
                'FaceColor', [0 0.4470 0.7410], ...
                'EdgeColor', 'none');

            tcp = surface(...
                'Parent',   axesHandle,...
                'XData',    ones(21)*p_JointCenter(1,9)+0.5*sphereXOffset,...
                'YData',    ones(21)*p_JointCenter(2,9)+0.5*sphereYOffset,...
                'ZData',    zeros(21),...
                'FaceColor', [1 0 0],...
                'EdgeColor', 'none');

            axesWidth = obj.AxesWidth;
            axesHeight = obj.AxesHeight;
            axesOrigin = axesHandle.Position(1:2);
            timeField = uicontrol(...
                'Parent',             obj.figObj,...
                'Style',              'text',...
                'Units',              'pixel', ...
                'Position',           [axesOrigin(1)+axesWidth-105 axesOrigin(2)+axesHeight-23 100 18],...
                'HorizontalAlignment','center',...
                'FontSize',           11,...
                'FontWeight',         'bold',...
                'String',             sprintf('Time: %0.2f s', initTime));

            actManipStruct.links = links;
            actManipStruct.joints = joints;
            actManipStruct.tcpBase = tcpBase;
            actManipStruct.tcpLeftGripper = tcpLeftGripper;
            actManipStruct.tcpRightGripper = tcpRightGripper;
            actManipStruct.tcp = tcp;
            actManipStruct.timeField = timeField;

            refManipStruct.links = copyobj(links, axesHandle);
            refManipStruct.joints = copyobj(joints, axesHandle);
            refManipStruct.tcpBase = copyobj(tcpBase, axesHandle);
            refManipStruct.tcpLeftGripper = copyobj(tcpLeftGripper, axesHandle);
            refManipStruct.tcpRightGripper = copyobj(tcpRightGripper, axesHandle);
            refManipStruct.tcp = copyobj(tcp, axesHandle);
            fieldNames = fieldnames(refManipStruct);
            for iField = 1:numel(fieldNames)
                currField = refManipStruct.(fieldNames{iField});
                if ~isempty(currField)
                    if numel(currField) > 1 && isprop(currField(1), 'FaceAlpha')
                        arrayfun(@(s)set(s, 'FaceAlpha', 0.2), refManipStruct.(fieldNames{iField}));
                    elseif isprop(currField, 'FaceAlpha')
                        set(currField, 'FaceAlpha', 0.2)
                    end
                end
            end
        end

        function updateSingleManipulator(~, p_JointCenter, phi, t, manipStruct)

            linkWidth = 0.030;
            linkXOffset = linkWidth*cos(phi);
            linkXOffset(1) = 8*linkXOffset(1);
            linkYOffset = linkWidth*sin(phi);
            p_JointCenter(2,1) = p_JointCenter(2,1) + 0.045;
            [sphereXOffset, sphereYOffset] = sphere(20);
            sphereXOffset = 0.045*sphereXOffset;
            sphereYOffset = 0.045*sphereYOffset;

            for iLink = 1:numel(manipStruct.links)
                currLinkXOffset = linkXOffset(iLink);
                currLinkYOffset = linkYOffset(iLink);
                XData = [...
                    p_JointCenter(1,iLink+1)-currLinkXOffset, p_JointCenter(1,iLink+1)+currLinkXOffset;
                    p_JointCenter(1,iLink)-currLinkXOffset,   p_JointCenter(1,iLink)+currLinkXOffset];
                YData = [...
                    p_JointCenter(2,iLink+1)-currLinkYOffset, p_JointCenter(2,iLink+1)+currLinkYOffset;
                    p_JointCenter(2,iLink)-currLinkYOffset,   p_JointCenter(2,iLink)+currLinkYOffset];

                set(manipStruct.links(iLink),...
                    'XData',    XData,...
                    'YData',    YData);
            end

            for iJoint = 1:numel(manipStruct.joints)
                if iJoint > 1
                    XData = ones(21)*p_JointCenter(1,iJoint)+sphereXOffset;
                    YData = ones(21)*p_JointCenter(2,iJoint)+sphereYOffset;
                else
                    XData = p_JointCenter(1,1) + 1.5 .* [-linkXOffset(1), linkXOffset(1);-linkXOffset(1), linkXOffset(1)];
                    YData = p_JointCenter(2,1) + [0, 0;-0.045, -0.045];
                end

                set(manipStruct.joints(iJoint),...
                    'XData',    XData,...
                    'YData',    YData);
            end

            set(manipStruct.tcpBase,...
                'XData',    [...
                p_JointCenter(1,8)-5*linkXOffset(6) p_JointCenter(1,8)+5*linkXOffset(6);
                p_JointCenter(1,7)-5*linkXOffset(6) p_JointCenter(1,7)+5*linkXOffset(6)],...
                'YData',    [...
                p_JointCenter(2,8)-5*linkYOffset(6) p_JointCenter(2,8)+5*linkYOffset(6);
                p_JointCenter(2,7)-5*linkYOffset(6) p_JointCenter(2,7)+5*linkYOffset(6)]);
            set(manipStruct.tcpLeftGripper,...
                'XData',    [...
                p_JointCenter(1,9)-3.5*linkXOffset(6) p_JointCenter(1,9)-2.0*linkXOffset(6);
                p_JointCenter(1,8)-3.5*linkXOffset(6) p_JointCenter(1,8)-2.0*linkXOffset(6)],...
                'YData',    [...
                p_JointCenter(2,9)-3.5*linkYOffset(6) p_JointCenter(2,9)-2.0*linkYOffset(6);
                p_JointCenter(2,8)-3.5*linkYOffset(6) p_JointCenter(2,8)-2.0*linkYOffset(6)]);
            set(manipStruct.tcpRightGripper,...
                'XData',    [...
                p_JointCenter(1,9)+2.0*linkXOffset(6) p_JointCenter(1,9)+3.5*linkXOffset(6);
                p_JointCenter(1,8)+2.0*linkXOffset(6) p_JointCenter(1,8)+3.5*linkXOffset(6)],...
                'YData',    [...
                p_JointCenter(2,9)+2.0*linkYOffset(6) p_JointCenter(2,9)+3.5*linkYOffset(6);
                p_JointCenter(2,8)+2.0*linkYOffset(6) p_JointCenter(2,8)+3.5*linkYOffset(6)]);

            set(manipStruct.tcp,...
                'XData',    ones(21)*p_JointCenter(1,9)+0.5*sphereXOffset,...
                'YData',    ones(21)*p_JointCenter(2,9)+0.5*sphereYOffset);

            if isfield(manipStruct, 'tcpTraj') && ~isempty(manipStruct.tcpTraj)
                set(manipStruct.tcpTraj,...
                    'XData',    [manipStruct.tcpTraj.XData, p_JointCenter(1,9)],...
                    'YData',    [manipStruct.tcpTraj.YData, p_JointCenter(2,9)]);
            end

            if isfield(manipStruct, 'timeField') && ~isempty(t)
                set(manipStruct.timeField,...
                    'String', sprintf('Time: %0.2f s', t));
            end

        end

        function [p_JointCenter, phi] = calcCartPosOfJointCenter(obj, q)
            import PlanarManipulatorViz.*

            Htm_O = eye(4,4);
            p_JointCenter = zeros(2,9);
            phi = zeros(1,6);
            for iLink = 1:6
                idxStart_4Row = 4*(iLink-1) + 1;
                idxEnd_4Row = idxStart_4Row + 3;
                idxStart_6Row = 6*(iLink-1) + 1;
                idxEnd_6Row = idxStart_6Row + 5;

                relBodyJac = obj.csi(idxStart_6Row:idxEnd_6Row);
                relHtm_def = obj.g0(idxStart_4Row:idxEnd_4Row, 1:4);
                relBodyJac = reshape(relBodyJac, 6, 1);

                relHtm = relHtm_def * Exponential(relBodyJac, q(iLink));
                Htm_O = Htm_O * relHtm;
                p_JointCenter(:,iLink) = Htm_O(2:3, 4);

                if iLink < 2
                    phi(iLink) = 0;
                else
                    phi(iLink) = sum(q(2:iLink));
                end
            end

            tool_Lengh = obj.tcp_t_ee(3, 4);
            p_O_TCP = Htm_O * [
                0 0 0;
                0 0 0;
                0.65*tool_Lengh 0.75*tool_Lengh tool_Lengh;
                1 1 1];
            p_JointCenter(:,7:9) = p_O_TCP(2:3, :);
        end

    end

    %% static methods
    methods (Static)

        function out = Skew(vec)
            % Skew operator
            out = [
                0         -vec(3)   vec(2)
                vec(3)    0         -vec(1)
                -vec(2)   vec(1)    0
                ];
        end

        function out = Exponential(csi, theta)
            % Twist exponential of the relative body jacobian
            o = [0 0 0].';
            I = eye( 3 );
            v = csi(1:3);
            w = csi(4:6);
            if all( w == o )
                out = [I v*theta; zeros(1,3) 1];
            else
                w_hat = PlanarManipulatorViz.Skew( w );
                R_minus_I = w_hat * sin( theta ) + w_hat * w_hat * ( 1 - cos(theta) );
                out = [I+R_minus_I zeros(3,1); zeros(1,3) 1];
            end
        end

    end
end