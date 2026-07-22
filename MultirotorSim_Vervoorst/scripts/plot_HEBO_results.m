n = 350; % Replace with your desired number

% Assuming reward and arm_length are already defined
% Sort the rewards in descending order and get the indices
[sorted_rewards, indices] = sort(reward, 'descend');

% Get the top n rewards and corresponding arm length parameters
top_n_rewards = sorted_rewards(1:n)';
top_n_arm_lengths = arm_length(indices(1:n), :);

% Get the lowest n rewards and corresponding arm length parameters
lowest_n_rewards = sorted_rewards(end-n+1:end)';
lowest_n_arm_lengths = arm_length(indices(end-n+1:end), :);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

reward_plot = reward';  % Assuming reward is a column vector

x = arm_length(:, 1);  % Extract first column of arm_length
y = arm_length(:, 2);  % Extract second column of arm_length
z = reward_plot;       % Your third dimension

% Create the scatter plot
scatter3(x, y, z, 36, z, 'filled');  % 'filled' fills the markers with color

% Adjust the colormap
colormap(jet);  % 'jet' is an example, you can choose others like 'hot', 'cool', etc.

% Set the color limits to focus on the range of interest
caxis([1100 max(reward_plot)]);

% Add color bar to indicate what each color represents in terms of the reward
colorbar;

% Labeling the axes
xlabel('Arm Length Dimension 1');
ylabel('Arm Length Dimension 2');
zlabel('Reward');

% Adding a title
title('3D Plot of Reward vs. Arm Length');

% Turn on the grid for better visualization
grid on;


n = 50; % Replace with your desired number

% Assuming reward and arm_length are already defined
% Sort the rewards in descending order and get the indices
[sorted_rewards, indices] = sort(reward, 'descend');

% Get the top n rewards and corresponding arm length parameters
top_n_rewards = sorted_rewards(1:n)';
top_n_arm_lengths = arm_length(indices(1:n), :);

% Get the lowest n rewards and corresponding arm length parameters
lowest_n_rewards = sorted_rewards(end-n+1:end)';
lowest_n_arm_lengths = arm_length(indices(end-n+1:end), :);


% Create a new figure window
figure;

% Plot for xz plane (Arm Length Dimension 1 vs Reward)
subplot(1, 2, 1);
plot(x, z, '.'); % 'o' for circle markers
xlabel('Arm Length Dimension 1');
ylabel('Reward');
title('XZ Plane: Arm Length Dimension 1 vs Reward');

% Plot for yz plane (Arm Length Dimension 2 vs Reward)
subplot(1, 2, 2);
plot(y, z, '.'); % 'o' for circle markers
xlabel('Arm Length Dimension 2');
ylabel('Reward');
title('YZ Plane: Arm Length Dimension 2 vs Reward');

% Enhance layout
sgtitle('Visualizing XZ and YZ Planes');
