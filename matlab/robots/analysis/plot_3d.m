repoRoot = fileparts(fileparts(fileparts(fileparts(mfilename('fullpath')))));

n = 120; % Number of points to consider
fontSize = 16; % Font size for the plots
figure; % Create a new figure

% Pre-define the color limits for consistency across all subplots
cmin = 50;
cmax = max(reward);

% Loop to create 6 subplots
for i = 0:4:20
    limits = n; % Limit for the number of points to plot

    n_min = i * 500 + 1;
    n_max = n_min + 499;

    % Get the top n rewards and corresponding arm length parameters
    top_n_rewards = reward(n_min:n_max)';
    top_n_arm_lengths = arm_length(n_min:n_max, :);

    % Assuming 'reward' and 'arm_length' are already defined
    x = top_n_arm_lengths(1:limits, 2); % First column of arm_length for X-axis
    y = top_n_arm_lengths(1:limits, 3); % Second column of arm_length for Y-axis
    z = top_n_arm_lengths(1:limits, 4); % Third column of arm_length for Z-axis
    reward_plot = top_n_rewards(1:limits); % Reward values for color-coding

    % Select subplot position
    subplot(2, 3, i/4 + 1);
    scatter3(x, y, z, 10, reward_plot, 'filled'); % Create 3D scatter plot
    colormap(jet); % Using jet colormap
    caxis([cmin cmax]); % Setting consistent color axis limits across all subplots
    xlabel('Length 1', 'FontSize', fontSize);
    ylabel('Length 2', 'FontSize', fontSize);
    zlabel('Length 3', 'FontSize', fontSize);
    xlim([0.1 2]); % Setting x-axis limits
    ylim([0.1 2]); % Setting y-axis limits
    zlim([0.1 2]); % Setting z-axis limits

    grid on; % Turning grid on
    set(gca, 'FontSize', fontSize); % Setting font size for axes
end

% Add a single colorbar to the figure
cb = colorbar;
cb.Position = [0.92 0.11 0.02 0.815]; % Adjust the position and size of the colorbar
caxis([cmin cmax]); % Ensure the colorbar represents the same range as the subplots




% Assuming reward and arm_length are already defined
% Sort the rewards in descending order and get the indices
% [sorted_rewards, indices] = sort(reward, 'descend');

% Get the top n rewards and corresponding arm length parameters
% top_n_rewards = sorted_rewards(1:n)';
% top_n_arm_lengths = arm_length(indices(1:n), :);

% % Export the 3D plot
% exportgraphics(fig3D, fullfile(repoRoot, 'outputs', 'quadcopter', 'plots', '3DScatterPlot.pdf'), 'ContentType', 'vector');
%
% % [Your existing code for data preparation goes here]
%
% % Create and save XY plane plot
% figXY = figure;
% scatter(x, y, 20, reward_plot, 'filled');
% colormap(jet);
% caxis([min(reward) max(reward)]);
% xlabel('Arm Length Dimension 1', 'FontSize', fontSize);
% ylabel('Arm Length Dimension 2', 'FontSize', fontSize);
% colorbar;
% grid on;
% set(gca, 'FontSize', fontSize);
% exportgraphics(figXY, fullfile(repoRoot, 'outputs', 'quadcopter', 'plots', 'XY_Plane_ScatterPlot.pdf'), 'ContentType', 'vector');
%
% % Create and save YZ plane plot
% figYZ = figure;
% scatter(y, z, 20, reward_plot, 'filled');
% colormap(jet);
% caxis([min(reward) max(reward)]);
% xlabel('Arm Length Dimension 2', 'FontSize', fontSize);
% ylabel('Arm Length Dimension 3', 'FontSize', fontSize);
% colorbar;
% grid on;
% set(gca, 'FontSize', fontSize);
% exportgraphics(figYZ, fullfile(repoRoot, 'outputs', 'quadcopter', 'plots', 'YZ_Plane_ScatterPlot.pdf'), 'ContentType', 'vector');
%
% % Create and save XZ plane plot
% figXZ = figure;
% scatter(x, z, 20, reward_plot, 'filled');
% colormap(jet);
% caxis([min(reward) max(reward)]);
% xlabel('Arm Length Dimension 1', 'FontSize', fontSize);
% ylabel('Arm Length Dimension 3', 'FontSize', fontSize);
% colorbar;
% grid on;
% set(gca, 'FontSize', fontSize);
% exportgraphics(figXZ, fullfile(repoRoot, 'outputs', 'quadcopter', 'plots', 'XZ_Plane_ScatterPlot.pdf'), 'ContentType', 'vector');
