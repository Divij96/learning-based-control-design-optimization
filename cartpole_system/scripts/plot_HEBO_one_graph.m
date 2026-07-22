fig = figure;
set(fig, 'Units', 'normalized', 'Position', [0, 0, 1, 1]); % Fill the screen

colors = lines(4);
font = 16;
for k=1:4
    if k == 1
        load("src/cart_pole/rl/trained_model/Hebo_eval/CartPole_Hebo_callback_Tanh_Tsteps_12800000_lr_5e-05_hidden_sizes_256_reward_1.00.20.0_pole_length_0.5_freq_1_batchsizeHebo_20.mat")
    elseif k==2
        load("src/cart_pole/rl/trained_model/Hebo_eval/CartPole_Hebo_callback_Tanh_Tsteps_12800000_lr_5e-05_hidden_sizes_256_reward_1.00.20.05_pole_length_0.5_freq_1_batchsizeHebo_20.mat")
    elseif k==3
        load("src/cart_pole/rl/trained_model/Hebo_eval/CartPole_Hebo_callback_Tanh_Tsteps_12800000_lr_5e-05_hidden_sizes_256_reward_1.00.20.1_pole_length_0.5_freq_1_batchsizeHebo_20.mat")
    elseif k==4
        load("src/cart_pole/rl/trained_model/Hebo_eval/CartPole_Hebo_callback_Tanh_Tsteps_12800000_lr_5e-05_hidden_sizes_256_reward_1.00.20.2_pole_length_0.5_freq_1_batchsizeHebo_20.mat")
    end

    % Clear arrays for each k
    reward_box = [];
    pole_length_box = [];
    disp_start = 1;
    disp_end = length(pole_length);

    % Initialize arrays for bin centers, average rewards, and standard deviations
    % Assuming pole_length and reward are pre-defined arrays
    BinWidth_pole_length = 0.5;
    binEdges = 0.5:BinWidth_pole_length:10.5;  % Determine bin edges
    binCenters = (binEdges(1:end-1) + binEdges(2:end)) / 2;
    averageRewards = zeros(1, length(binCenters));
    stdDeviations = zeros(1, length(binCenters));

    for i = 1:length(binCenters)
        % Logical indexing to find pole_length values within current bin
        inBin = pole_length >= binEdges(i) & pole_length < binEdges(i+1);
        % Calculate average reward and standard deviation for current bin
        averageRewards(i) = mean(reward(inBin));
        stdDeviations(i) = std(reward(inBin));
    end

    % Plotting average rewards with standard deviation as error bars
    errorbar(binCenters, averageRewards, stdDeviations, 'o-', 'Color', colors(k, :), 'MarkerSize', 6, 'LineWidth', 2);
    hold on;
end

title('HEBO results', 'FontSize', font); % Adds a title to your figure with increased font size
xlabel('Pole Length in m', 'FontSize', font); % Adds a label to the x-axis with increased font size
ylabel('Rewards', 'FontSize', font); % Adds a label to the y-axis with increased font size
ylim([0, 5500]);
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
exportgraphics(fig, fullfile(repoRoot, 'cartpole_system', 'plots', 'hebo_plots', 'HEBO_results_cart_pole.pdf'), 'ContentType', 'vector');
hold off;
repoRoot = fileparts(fileparts(fileparts(mfilename('fullpath'))));
