
repoRoot = fileparts(fileparts(fileparts(fileparts(mfilename('fullpath')))));

% Define a matrix of 8 distinct colors
colors = lines(4);
windowSize = 20;
fontSize = 16; % Define the font size for all text in figures

% Create and maximize the figure
fig = figure;
set(fig, 'Units', 'normalized', 'Position', [0, 0, 1, 1]); % Fill the screen

num_dist = 1;
sub_plot_idx1 = num_dist;
sub_plot_idx2 = 2;

for i = 1:num_dist

    % Create a subplot for the current distribution
    subplot(sub_plot_idx1, sub_plot_idx2, 2*i-1); % 4 rows, 2 columns of subplots

    % Convert cell arrays to matrices for plotting
    mean_vals = dist_mean(i,:)';
    std_vals = dist_std(i,:)';

    % Create errorbar with distinct color
    h = errorbar(mean_vals, std_vals, '.', 'Color', colors(i, :));
    % Adjust errorbar color to be a lighter shade of the original color
    set(h, 'Color', colors(i,:) + (1-colors(i,:))*0.7); % Mixing the original color with white to lighten it
    set(h, 'MarkerEdgeColor', colors(i, :));
    set(h, 'LineWidth', 1); % Adjust the line width if necessary

    ylabel('Value');
    titleText = sprintf('Distribution %d - Final mean, std dev: %.2f, %.2f', i, dist_mean(i,end), dist_std(i,end));
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

    %%%%%%%%%%PLOT REWARD%%%%%%%%%%%%%%
    subplot(sub_plot_idx1, sub_plot_idx2, 2*i); % 4 rows, 2 columns of subplots

    % Original data
    plot(reward(i,:), 'Color', [0.7, 0.7, 0.7]); % Gray color for the original data
    hold on;

    % Smoothed data using a moving average
    smoothed_reward = movmean(reward(i,:), windowSize, 'omitnan');
    plot(smoothed_reward, '.','Color', colors(i, :), 'LineWidth', 1);
    %
    % legend('rewards', 'steps')

    % Labeling (optional)
    xlabel('Time Step');
    ylabel('reward');

    titleText = 'Reward';
    title(titleText);

        % Set font size for the current subplot
    ax = gca; % Get current axis
    ax.FontSize = fontSize;

    % Set font size for ylabel, xlabel, and title
    ylh = ylabel('Value');
    ylh.FontSize = fontSize; % Set font size for Y label

    xlh = xlabel('Time Step');
    xlh.FontSize = fontSize; % Set font size for X label

    tlh = title(titleText);
    tlh.FontSize = fontSize; % Set font size for title
    ylim([0 5500]);
    hold off;
end


% Explicitly specify figure size for exporting
set(fig, 'PaperPositionMode', 'auto');
drawnow; % Update figure window

% Export the figure as a PDF with vector content
exportgraphics(fig, fullfile(repoRoot, 'outputs', 'cart_pole', 'plots', 'schaff', 'schaff_results_cart_pole_dist4_reward_02.pdf'), 'ContentType', 'vector');
