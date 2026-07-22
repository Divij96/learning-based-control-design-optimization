import torch
import torch.distributions as D
import torch.nn.functional as F
import numpy as np
import torch.optim as optim

class DesignDistribution_log:
    def __init__(self, initial_mean, initial_std, lr_mean=0.1, lr_std=0.1, min_parameters=np.ones(4, dtype=np.float32), max_parameters=np.ones(4, dtype=np.float32)):
        self.mean = torch.tensor(initial_mean, dtype=torch.float32, requires_grad=True)
        self.std = torch.tensor(initial_std, dtype=torch.float32, requires_grad=True)
        self.min_parameters = min_parameters
        self.max_parameters = max_parameters
        self.optimizer_mean = optim.Adam([self.mean], lr=lr_mean)
        self.optimizer_std = optim.Adam([self.std], lr=lr_std)

    def update_distribution(self, batch_rewards, batch_samples):
        self.optimizer_mean.zero_grad()
        self.optimizer_std.zero_grad()

        for i, sample in enumerate(batch_samples):
            sample = torch.tensor(sample, dtype=torch.float32)
            softplus_std = F.softplus(self.std + 1e-6)  # 1e-6 is a small constant
            distribution = D.Normal(self.mean, softplus_std)
            neg_log_likelihood = -distribution.log_prob(sample).sum()
            loss = neg_log_likelihood * batch_rewards[i]
            loss.backward()

        self.optimizer_mean.step()
        self.optimizer_std.step()

        # Convert min_parameters and max_parameters to PyTorch tensors
        min_params_tensor = torch.tensor(self.min_parameters, dtype=torch.float32)
        max_params_tensor = torch.tensor(self.max_parameters, dtype=torch.float32)

        # Clamping the mean within the specified range
        with torch.no_grad():
            self.mean.clamp_(min=min_params_tensor, max=max_params_tensor)


    def sample_design(self):
        for _ in range(10):
            sample = D.Normal(self.mean, F.softplus(self.std)).sample()
            if torch.all(sample >= torch.tensor(self.min_parameters, dtype=torch.float32)) and torch.all(sample <= torch.tensor(self.max_parameters, dtype=torch.float32)):
                return sample
        # Handling out-of-bound samples
        sample = torch.max(torch.min(sample, torch.tensor(self.max_parameters, dtype=torch.float32)), torch.tensor(self.min_parameters, dtype=torch.float32))
        return sample

    def get_mean(self):
        return self.mean.detach().numpy()

    def get_std(self):
        return F.softplus(self.std).detach().numpy()


def reward_function(sampled_design):
    target_design = torch.tensor([10.0, 20.0, 30.0, 40.0], dtype=torch.float32)
    return torch.norm(abs(sampled_design) - abs(target_design)).item()

def main():
    mean = np.array([16.0, 34.0, 47.0, 32.0], dtype=np.float32)
    std = np.array([1.0, 1.0, 1.0, 1.0], dtype=np.float32)
    min_parameters = np.array([0.5, 0.5, 0.5, 0.5], dtype=np.float32)
    max_parameters = np.array([100.0, 200.0, 300.0, 400.0], dtype=np.float32)

    design_distribution = DesignDistribution_log(mean, std, min_parameters=min_parameters, max_parameters=max_parameters)
    batch_size = 1
    max_iterations = 100000

    for iteration in range(max_iterations):
        batch_rewards = []
        batch_samples = []

        for _ in range(batch_size):
            sampled_design = design_distribution.sample_design()
            reward = -reward_function(sampled_design)
            batch_samples.append(sampled_design)
            batch_rewards.append(reward)

        design_distribution.update_distribution(batch_rewards, batch_samples)

        if iteration % 10 == 0:
            print(f"Iteration {iteration}: Mean = {design_distribution.get_mean()}, Std = {design_distribution.get_std()}")

        # Insert a convergence check here if needed

if __name__ == "__main__":
    main()
