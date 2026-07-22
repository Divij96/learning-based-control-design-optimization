% Assuming pole_length and reward are pre-defined arrays

% % Scatter plot for reward against pole_length
% plot(pole_length(disp_start:disp_end), reward(disp_start:disp_end), '*');  % Create scatter plot
% xlabel('Pole Length');  % Label x-axis
% ylabel('Reward');  % Label y-axis
% title('Reward vs Pole Length');  % Set title

figure;  % Create a new figure window

colors = lines(4);

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

% Assuming pole_length and reward are pre-defined arrays
% figure;  % Create a new figure window
BinWidth_pole_length = 0.5;
binEdges = 0.5:BinWidth_pole_length:10.5;  % Determine bin edges

% Initialize arrays to hold bin centers and average rewards
binCenters = (binEdges(1:end-1) + binEdges(2:end))/2;
averageRewards = zeros(1,length(binCenters));

% Loop through each bin and calculate average reward
for i = 1:length(binCenters)
    % Logical indexing to find pole_length values within current bin
    inBin = pole_length >= binEdges(i) & pole_length < binEdges(i+1);
    % Calculate average reward for current bin
    averageRewards(i) = mean(reward(inBin));
    %boxplot data
    for j = 1:length(reward)
        if inBin(j) == 1
            reward_box(j) = reward(j);
            pole_length_box(j) = binCenters(i);
        end
    end
end


% boxplot(reward_box, pole_length_box, 'Color', colors(k, :))
title('HEBO results') % Adds a title to your figure
xlabel('Pole Length in m') % Adds a label to the x-axis
ylabel('Rewards') % Adds a label to the y-axis
ylim([0 5500]);

% Overlay the mean values on the boxplot
hold on;
% mappedPositions = (1:length(averageRewards))/2';
mappedPositions = (0.5:BinWidth_pole_length:10)';

    plot(mappedPositions, averageRewards, 'Marker', 'o', 'MarkerSize', 6, 'LineWidth', 2, 'Color', colors(k, :));
end
legendLabels{1} = sprintf('action penalty %.2f', 0.0);
legendLabels{2} = sprintf('action penalty %.2f', 0.05);
legendLabels{3} = sprintf('action penalty %.2f', 0.1);
legendLabels{4} = sprintf('action penalty %.2f', 0.2);
% Adjust legend
legend(legendLabels, 'Location', 'best', 'FontWeight', 'bold');
hold off;


% figure;
% % Assuming pole_length and reward are your arrays and they are of the same length
% % Sort the rewards in descending order and get the sorting indices
% [sorted_rewards, sort_indices] = sort(reward, 'descend');
% % Reorder the pole lengths array using the sorting indices
% sorted_pole_lengths = pole_length(sort_indices);
% size = 100;
% % Extract the top 10 rewards and their corresponding pole lengths
% top_rewards = sorted_rewards(1:size);
% top_pole_lengths = sorted_pole_lengths(1:size);
% plot(top_pole_lengths, top_rewards, '*');  % Create scatter plot
% title('Top 100 rewards and corresponding pole lengths') % Adds a title to your figure
% xlabel('Pole Length in m') % Adds a label to the x-axis
% ylabel('Rewards') % Adds a label to the y-axis
% % Set the y-axis range from 0 to 10
% ylim([4800 5200]);
% xlim([0 10]);
% % Display the results
% disp('Top 10 rewards and corresponding pole lengths:');
% for i = 1:10
%     fprintf('Pole Length: %.2f, Reward: %.2f\n', top_pole_lengths(i), top_rewards(i));
% end