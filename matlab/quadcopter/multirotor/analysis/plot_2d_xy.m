repoRoot = fileparts(fileparts(fileparts(fileparts(fileparts(mfilename('fullpath'))))));

% Constants and initial data setup
n = 950; % Number of points to consider
fontSize = 16; % Font size for the plots
limits = n; % Limit for the number of points to plot

% Assuming reward and arm_length are already defined
% Sort the rewards in descending order and get the indices
[sorted_rewards, indices] = sort(reward, 'descend');

% Get the top n rewards and corresponding arm length parameters
top_n_rewards = sorted_rewards(1:n)';
top_n_arm_lengths = arm_length(indices(1:n), :);

[sorted_rewards, indices] = sort(reward, 'descend');

% Get the top n rewards and corresponding arm length parameters
top_n_rewards = reward(1:n)';
top_n_arm_lengths = arm_length(1:n, :);

% Assuming 'reward' and 'arm_length' are already defined
x = top_n_arm_lengths(1:limits, 1); % First column of arm_length for X-axis
y = top_n_arm_lengths(1:limits, 2); % Second column of arm_length for Y-axis
z = top_n_rewards(1:limits)'; % Reward values for color-coding

% Create the 2D scatter plot
fig2D = figure;
scatter(x, y, 30, z, 'filled'); % 'filled' fills the markers with color
colormap(jet); % Using jet colormap
caxis([400 max(reward)]); % Setting color axis limits based on reward range
cb = colorbar; % Adding colorbar
cb.FontSize = fontSize; % Setting font size for colorbar
xlabel('Arm Length Dimension 1 and 2', 'FontSize', fontSize);
ylabel('Arm Length Dimension 3 and 4', 'FontSize', fontSize);
title('2D Scatter Plot of Arm Lengths with Reward', 'FontSize', fontSize);
grid on; % Turning grid on
set(gca, 'FontSize', fontSize); % Setting font size for axes

% Export the 2D plot
set(fig2D, 'PaperPositionMode', 'auto'); % Setting paper position mode
drawnow; % Ensure the figure is rendered before saving
exportgraphics(fig2D, fullfile(repoRoot, 'outputs', 'quadcopter', 'plots', '2DScatterPlot_quadcpoter_corr_1500.pdf'), 'ContentType', 'vector');
