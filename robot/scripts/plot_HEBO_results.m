fontSize = 10;  % Define a constant font size
limits = 50;
x = arm_length(1:limits, 1);  % Extract first column of arm_length
y = arm_length(1:limits, 2);  % Extract second column of arm_length
z = reward(1:limits)';        % Your reward data

% Determine common tick interval for both X and Y axes
commonTickInterval = 1;  % Set the interval you desire
xTicks = 1:commonTickInterval:5;
yTicks = 1:commonTickInterval:5;


% Create the 2D scatter plot
fig2D = figure;
scatter(x, y, 10, z, 'filled');  % 'filled' fills the markers with color
colormap(jet);
caxis([1000 2000]);
cb = colorbar;
cb.FontSize = fontSize;
xlabel('Link length dimension 1', 'FontSize', fontSize);
ylabel('Link length dimension 2', 'FontSize', fontSize);
title('Plot of link lengths with reward', 'FontSize', fontSize);
grid on;
set(gca, 'FontSize', fontSize, 'XTick', xTicks, 'YTick', yTicks);

% Export the 2D plot
set(fig2D, 'PaperPositionMode', 'auto');
drawnow;
exportgraphics(fig2D, fullfile(repoRoot, 'robot', 'plots', 'Robot2DScatterPlot_50designs.pdf'), 'ContentType', 'vector');

% Create the 3D scatter plot
fig3D = figure;
scatter3(x, y, z, 10, z, 'filled'); % 'filled' fills the markers with color
colormap(jet);
caxis([1000 2000]);
cb = colorbar;
cb.FontSize = fontSize;
xlabel('Link length dimension 1', 'FontSize', fontSize);
ylabel('Link length dimension 2', 'FontSize', fontSize);
zlabel('Reward', 'FontSize', fontSize);
title('3D Plot of Link Lengths and Reward', 'FontSize', fontSize);
grid on;
set(gca, 'FontSize', fontSize);
view(-30, 10);  % Adjust for a good viewing angle

% Export the 3D plot
set(fig3D, 'PaperPositionMode', 'auto');
drawnow;
exportgraphics(fig3D, fullfile(repoRoot, 'robot', 'plots', 'Robot3DScatterPlot.pdf'), 'ContentType', 'vector');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Prepare data for the top and lowest n rewards
n = 50; % Replace with your desired number

% Sort the rewards in descending order and get the indices
[sorted_rewards, indices] = sort(reward, 'descend');

% Get the top n rewards and corresponding arm length parameters
top_n_rewards = sorted_rewards(1:n)';
top_n_arm_lengths = arm_length(indices(1:n), :);

% Get the lowest n rewards and corresponding arm length parameters
lowest_n_rewards = sorted_rewards(end-n+1:end)';
lowest_n_arm_lengths = arm_length(indices(end-n+1:end), :);

% Create a new figure window for subplots
figure;

% Plot for xz plane (Arm Length Dimension 1 vs Reward)
subplot(1, 2, 1);
plot(x, z, 'o'); % 'o' for circle markers
xlabel('Link length dimension 1', 'FontSize', fontSize);
ylabel('Reward', 'FontSize', fontSize);
title('XZ Plane: Arm Length Dimension 1 vs Reward', 'FontSize', fontSize);
set(gca, 'FontSize', fontSize);

% Plot for yz plane (Arm Length Dimension 2 vs Reward)
subplot(1, 2, 2);
plot(y, z, 'o'); % 'o' for circle markers
xlabel('Link length dimension 2', 'FontSize', fontSize);
ylabel('Reward', 'FontSize', fontSize);
title('YZ Plane: Arm Length Dimension 2 vs Reward', 'FontSize', fontSize);
% Turn on the grid for better visualization
grid on;

% Set font size for axes tick labels
set(gca, 'FontSize', fontSize);
repoRoot = fileparts(fileparts(fileparts(mfilename('fullpath'))));
