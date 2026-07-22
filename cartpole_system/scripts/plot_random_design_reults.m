repoRoot = fileparts(fileparts(fileparts(mfilename('fullpath'))));

% Step 1: Load Data
data1 = readtable(fullfile(repoRoot, 'src', 'scara_2dof_robot', 'result_tb', 'TB_ScaraRobot_FilterOn_length_random_design_start_upd_25lr_mean0.01_std_0.01_sdeFalse_Tanh_Tsteps_409600000_lr_0.001_hidden_sizes_50_POSreward_1.0_VELreward_0.0_omega_pen_0.0_var_design_PPO_1.csv'));


% Step 3: Create the Plot
fig = figure; % Create a new figure window
font = 16;
colors = lines(4);
set(fig, 'Units', 'normalized', 'Position', [0, 0, 1, 1]); % Fill the screen

hold on
plot(data1.Step, data1.Value,'Color', colors(1, :)); % Plot time vs value

title('rewards vs time steps plot', 'FontSize', font); % Adds a title to your figure with increased font size
xlabel('time step', 'FontSize', font); % Adds a label to the x-axis with increased font size
ylabel('Rewards', 'FontSize', font); % Adds a label to the y-axis with increased font size
ylim([0, 2200]);
% Change the font size of the tick labels
ax = gca; % Get handle to current axes
ax.FontSize = font; % Set the font size for tick labels



% Explicitly specify figure size for exporting
set(fig, 'PaperPositionMode', 'auto');
drawnow; % Update figure window

% Export the figure as a PDF with vector content
exportgraphics(fig, fullfile(repoRoot, 'robot', 'plots', 'random_design_planar_robot.pdf'), 'ContentType', 'vector');
hold off;
