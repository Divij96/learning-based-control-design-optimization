clear all
figure;  % Create a new figure window

colors = lines(4);
font = 16;
batch_size = 10;
for k=1:4
    if k == 1
        load("python/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.0_freq_1.mat")
    elseif k==2
        load("python/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.05_freq_1.mat")
    elseif k==3
        load("python/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.1_freq_1.mat")
    elseif k==4
        load("python/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.2_freq_1.mat")
    end
    pole_length = pole_length';
    averageRewards = zeros(length(rewards)/batch_size,1);
    stdDeviations = zeros(length(rewards)/batch_size,1);
    binCenters = zeros(length(rewards)/batch_size,1);

    for i = 1:length(binCenters)
        % Calculate average reward and standard deviation for current bin
        averageRewards(i) = mean(rewards((i-1)*batch_size+1:i*batch_size));
        % stdDeviations(i) = std(rewards((i-1)*batch_size+1:i*batch_size));
        binCenters(i) = mean(pole_length((i-1)*batch_size+1:i*batch_size));
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

hold off;