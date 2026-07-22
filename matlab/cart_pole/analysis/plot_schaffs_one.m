repoRoot = fileparts(fileparts(fileparts(fileparts(mfilename('fullpath')))));

%prepare data

load("python/cart_pole/rl/trained_model/schaff_chop/matlab_data/long_training/CartPole_Schaff_callback_Tanh_Tsteps_61440000_lr_5e-05_hidden_sizes_256_reward_1.00.20.0_pole_length_0.5_freq_1_schaff_lr0.1_0_num_dist_1.mat")
reward_new(1,:) = reward(1,:);
dist_std_new(1,:) = dist_std(1,:);
dist_mean_new(1,:)= dist_mean(1,:);
load("python/cart_pole/rl/trained_model/schaff_chop/matlab_data/long_training/CartPole_Schaff_callback_Tanh_Tsteps_61440000_lr_5e-05_hidden_sizes_256_reward_1.00.20.05_pole_length_0.5_freq_1_schaff_lr0.1_0_num_dist_1.mat")
reward_new(2,:) = reward(1,:);
dist_std_new(2,:) = dist_std(1,:);
dist_mean_new(2,:)= dist_mean(1,:);
load("python/cart_pole/rl/trained_model/schaff_chop/matlab_data/long_training/CartPole_Schaff_callback_Tanh_Tsteps_61440000_lr_5e-05_hidden_sizes_256_reward_1.00.20.1_pole_length_0.5_freq_1_schaff_lr0.1_0_num_dist_1.mat")
reward_new(3,:) = reward(1,:);
dist_std_new(3,:) = dist_std(1,:);
dist_mean_new(3,:)= dist_mean(1,:);
load("python/cart_pole/rl/trained_model/schaff_chop/matlab_data/long_training/CartPole_Schaff_callback_Tanh_Tsteps_61440000_lr_5e-05_hidden_sizes_256_reward_1.00.20.2_pole_length_0.5_freq_1_schaff_lr0.1_0_num_dist_1.mat")
reward_new(4,:) = reward(1,:);
dist_std_new(4,:) = dist_std(1,:);
dist_mean_new(4,:)= dist_mean(1,:);


% Define a matrix of 8 distinct colors
colors = lines(4);
windowSize = 40;
fontSize = 16; % Define the font size for all text in figures
% Create and maximize the figure
fig = figure;
set(fig, 'Units', 'normalized', 'Position', [0, 0, 1, 1]); % Fill the screen

subplot(1, 2, 1); % One row, two columns of subplots

for i = 1:4
    hold on;

    % Convert cell arrays to matrices for plotting
    mean_vals = dist_mean_new(i,:)';
    std_vals = dist_std_new(i,:)';

    % Create errorbar with distinct color
    h = errorbar(mean_vals, std_vals, '.', 'Color', colors(i, :));
    set(h, 'CapSize', 0); % Remove the caps
    % Adjust transparency (undocumented feature)
    alpha = 0.15; % Set transparency level
    set([h.Bar, h.Line], 'ColorType', 'truecoloralpha', 'ColorData', [h.Line.ColorData(1:3); 255*alpha]);
    % Set legend labels
    % Plot an invisible line for the legend
    legendHandles(i) = plot(NaN, NaN, 'Color', colors(i, :), 'LineWidth', 2); % A thicker line for visibility

    % Set legend labels
    ylabel('Pole length in m');
    titleText = sprintf('Gaussian distributions');
    title(titleText);
    % Set font size for the current subplot
    ax = gca; % Get current axis
    ax.FontSize = fontSize;

    % Set font size for ylabel, xlabel, and title
    ylh = ylabel('Pole length in m');
    ylh.FontSize = fontSize; % Set font size for Y label

    xlh = xlabel('Time Step');
    xlh.FontSize = fontSize; % Set font size for X label

    tlh = title(titleText);
    tlh.FontSize = fontSize; % Set font size for title

    % Set the y-axis range from 0 to 10
    ylim([0.5 10]);
end
% Add legend to the first subplot
legendLabels{1} = sprintf('action penalty %.2f, Final mean: %.2f, std dev: %.2f', 0.0, dist_mean_new(1,end), dist_std_new(1,end)');
legendLabels{2} = sprintf('action penalty %.2f, Final mean: %.2f, std dev: %.2f', 0.05, dist_mean_new(2,end), dist_std_new(2,end)');
legendLabels{3} = sprintf('action penalty %.2f, Final mean: %.2f, std dev: %.2f', 0.1, dist_mean_new(3,end), dist_std_new(3,end)');
legendLabels{4} = sprintf('action penalty %.2f, Final mean: %.2f, std dev: %.2f', 0.2, dist_mean_new(4,end), dist_std_new(4,end)');

legend(legendHandles, legendLabels, 'Location', 'best', 'FontWeight', 'bold');
hold off

%%%%%%%%%%PLOT REWARD%%%%%%%%%%%%%%
for i = 1:4
    hold on;
    subplot(1, 2, 2); % 4 rows, 2 columns of subplots

    % Original data
    % plot(reward_new(i,:), 'Color', [0.95, 0.95, 0.95]); % Gray color for the original data

    % Smoothed data using a moving average
    smoothed_reward = movmean(reward_new(i,:), windowSize, 'omitnan');
    plot(smoothed_reward, '.','Color', colors(i, :), 'LineWidth', 2);
    %
    % legend('rewards', 'steps')

    % Labeling (optional)
    xlabel('Time Step');
    ylabel('reward');
    title('Reward');
        % Set font size for the current subplot
    ax = gca; % Get current axis
    ax.FontSize = fontSize;

    titleText = sprintf('Rewards');
    title(titleText);

    % Set font size for ylabel, xlabel, and title
    ylh = ylabel('Rewards');
    ylh.FontSize = fontSize; % Set font size for Y label

    xlh = xlabel('Time Step');
    xlh.FontSize = fontSize; % Set font size for X label

    tlh = title(titleText);
    tlh.FontSize = fontSize; % Set font size for title
    ylim([0 5500]);
end

hold off;


% Explicitly specify figure size for exporting
set(fig, 'PaperPositionMode', 'auto');
drawnow; % Update figure window

% Export the figure as a PDF with vector content
exportgraphics(fig, fullfile(repoRoot, 'outputs', 'cart_pole', 'plots', 'schaff', 'schaff_results_cart_pole.pdf'), 'ContentType', 'vector');
