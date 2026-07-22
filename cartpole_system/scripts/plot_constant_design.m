clear all
figure;  % Create a new figure window

colors = lines(4);
font = 16;
batch_size = 10;
for k=1:4
    rewards = [];
    pole_length = [];
    if k == 1
        load("src/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.0_freq_1.mat")
    elseif k==2
        load("src/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.05_freq_1.mat")
    elseif k==3
        load("src/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.1_freq_1.mat")
    elseif k==4
        load("src/cart_pole/rl/trained_model/constant_mass/new_matlab_results/CartPole_constant_design_Tanh_Tsteps_5120000_lr_0.0001_hidden_sizes_256_reward_1.00.20.2_freq_1.mat")
    end
    pole_length = pole_length'; % Transpose pole_length if necessary

    boxplot(rewards, pole_length, 'Colors', colors(k, :));
    hold on
end

title('constant results', 'FontSize', font); % Adds a title to your figure with increased font size
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