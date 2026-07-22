repoRoot = fileparts(fileparts(fileparts(fileparts(mfilename('fullpath')))));

% Step 1: Load Data
data1 = readtable(fullfile(repoRoot, 'python', 'cart_pole', 'results_tensorboard', 'TB_CartPole_random_design_Tanh_Tsteps_51200000_lr_5e-05_hidden_sizes_256_reward_1.00.20.0_pole_length_1.0_freq_1_PPO_1.csv'));
data2 = readtable(fullfile(repoRoot, 'python', 'cart_pole', 'results_tensorboard', 'TB_CartPole_random_design_Tanh_Tsteps_51200000_lr_5e-05_hidden_sizes_256_reward_1.00.20.05_pole_length_0.5_freq_1_PPO_1.csv'));
data3 = readtable(fullfile(repoRoot, 'python', 'cart_pole', 'results_tensorboard', 'TB_CartPole_random_design_Tanh_Tsteps_51200000_lr_5e-05_hidden_sizes_256_reward_1.00.20.1_pole_length_1.0_freq_1_PPO_1.csv'));
data4 = readtable(fullfile(repoRoot, 'python', 'cart_pole', 'results_tensorboard', 'TB_CartPole_random_design_Tanh_Tsteps_51200000_lr_5e-05_hidden_sizes_256_reward_1.00.20.2_pole_length_1.0_freq_1_PPO_1.csv'));


% Step 3: Create the Plot
fig = figure; % Create a new figure window
font = 16;
colors = lines(4);
set(fig, 'Units', 'normalized', 'Position', [0, 0, 1, 1]); % Fill the screen

hold on
plot(data1.Step, data1.Value,'Color', colors(1, :)); % Plot time vs value
plot(data2.Step, data2.Value,'Color', colors(2, :)); % Plot time vs value
plot(data3.Step, data3.Value,'Color', colors(3, :)); % Plot time vs value
plot(data4.Step, data4.Value,'Color', colors(4, :)); % Plot time vs value

title('rewards vs time steps plot', 'FontSize', font); % Adds a title to your figure with increased font size
xlabel('time step', 'FontSize', font); % Adds a label to the x-axis with increased font size
ylabel('Rewards', 'FontSize', font); % Adds a label to the y-axis with increased font size
ylim([0, 5300]);
% Change the font size of the tick labels
ax = gca; % Get handle to current axes
ax.FontSize = font; % Set the font size for tick labels

% Setting up the legend
legendLabels{1} = sprintf('action penalty %.2f', 0.0);
legendLabels{2} = sprintf('action penalty %.2f', 0.05);
legendLabels{3} = sprintf('action penalty %.2f', 0.1);
legendLabels{4} = sprintf('action penalty %.2f', 0.2);
legend(legendLabels, 'Location', 'best', 'FontWeight', 'bold', 'FontSize', font);


% Explicitly specify figure size for exporting
set(fig, 'PaperPositionMode', 'auto');
drawnow; % Update figure window

% Export the figure as a PDF with vector content
exportgraphics(fig, fullfile(repoRoot, 'outputs', 'cart_pole', 'plots', 'random_dist', 'random_design_cartpole.pdf'), 'ContentType', 'vector');
hold off;
