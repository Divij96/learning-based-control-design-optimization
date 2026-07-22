clear res
vizStep =  0.05/Ts;
vizTout = tout(1:vizStep:end);
res.q_PD = q_PD(1:vizStep:end, :);
res.q_AugPD = q_AugPD(1:vizStep:end, :);
res.q_CompTorq = q_CompTorq(1:vizStep:end, :);
res.q_Robust = q_Robust(1:vizStep:end, :);
res.q_des = q_des(1:vizStep:end, :);

if ~exist('viz', 'var') || ~isvalid(viz.figObj)
    viz = PlanarManipulatorViz(ROBOT.g0, ROBOT.csi, ROBOT.tcp_t_ee, q0);
end

viz.runVisualization(vizTout, res)