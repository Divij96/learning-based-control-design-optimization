# import numpy as np

# # Constants
# total_cost = 500
# return_charge = 230
# return_percentage = 45 / 100  # Convert percentage to decimal
# commission_rate_low = 17 / 100  # Commission rate for selling price between 500 and 800
# commission_rate_high = 19 / 100  # Commission rate for selling price above 800
# fixed_online_retailer_fee = 150  # Fixed online retailer fee
# demand_decrease_rate = 0 / 100  # 1% decrease in demand for every $10 increase in price above $500
# base_demand = 1  # Normalized base demand

# # Function to calculate commission based on selling price
# def calculate_commission(selling_price):
#     if 500 <= selling_price <= 800:
#         return selling_price * commission_rate_low
#     elif selling_price > 800:
#         return selling_price * commission_rate_high
#     else:
#         return 0

# # Function to calculate expected profit for a given selling price considering the fixed online retailer fee and demand decrease
# def calculate_expected_profit_with_demand(selling_price):
#     # Calculate decrease in demand based on price increase above $500
#     if selling_price > 500:
#         demand_decrease = ((selling_price - 500) / 10) * demand_decrease_rate
#     else:
#         demand_decrease = 0
#     adjusted_demand = base_demand - demand_decrease

#     commission = calculate_commission(selling_price)
#     net_profit_per_sale = selling_price - total_cost - commission - fixed_online_retailer_fee
#     # Adjusting for return percentage, return charge, and decreased demand
#     expected_profit = ((net_profit_per_sale * (1 - return_percentage)) - (return_charge * return_percentage)) * adjusted_demand
#     return expected_profit

# # Analyze a range of selling prices to find the optimal price
# selling_prices = np.arange(500, 1200, 5)  # Analyze from $500 to $1500 in $5 increments
# profits_with_demand = [calculate_expected_profit_with_demand(price) for price in selling_prices]
# optimal_price_index_with_demand = np.argmax(profits_with_demand)
# optimal_price_with_demand = selling_prices[optimal_price_index_with_demand]
# optimal_profit_with_demand = profits_with_demand[optimal_price_index_with_demand]

# # Print the optimal selling price and the expected profit
# print(f"Optimal Selling Price: ${optimal_price_with_demand}")
# print(f"Expected Profit: ${optimal_profit_with_demand:.2f}")


import pandas as pd
import numpy  as np
from hebo.design_space.design_space import DesignSpace
from hebo.optimizers.hebo import HEBO

def obj(params : pd.DataFrame) -> np.ndarray:
    return ((params.values - 0.37)**2).sum(axis = 1).reshape(-1, 1)

space = DesignSpace().parse([{'name' : 'x', 'type' : 'num', 'lb' : -3, 'ub' : 3}])
opt   = HEBO(space)
for i in range(5):
    rec = opt.suggest(n_suggestions = 4)
    opt.observe(rec, obj(rec))
    print(obj(rec))
    # print('After %d iterations, best obj is %.2f' % (i, opt.y.min()))