#!/usr/bin/env python3
"""
HashmonkeyCoin Total Supply Calculator
Calculates the maximum total supply based on block reward and halving schedule
"""

def calculate_total_supply():
    # HashmonkeyCoin parameters
    initial_block_reward = 500  # HMNY per block
    halving_interval = 210240   # blocks per halving
    block_time_minutes = 2      # minutes per block
    
    print("HashmonkeyCoin Total Supply Calculation")
    print("=" * 50)
    print(f"Initial Block Reward: {initial_block_reward} HMNY")
    print(f"Halving Interval: {halving_interval:,} blocks")
    print(f"Block Time: {block_time_minutes} minutes")
    print(f"Halving Period: {halving_interval * block_time_minutes / (365.25 * 24 * 60):.1f} years")
    print()
    
    total_supply = 0
    current_reward = initial_block_reward
    halving_count = 0
    
    print("Halving Schedule:")
    print("-" * 50)
    
    while current_reward >= 1:  # Continue until reward is less than 1 HMNY
        blocks_in_this_era = halving_interval
        era_supply = blocks_in_this_era * current_reward
        total_supply += era_supply
        
        print(f"Era {halving_count + 1}: {current_reward:>6.0f} HMNY/block × {blocks_in_this_era:>6,} blocks = {era_supply:>12,.0f} HMNY")
        
        current_reward = current_reward / 2
        halving_count += 1
        
        # Stop after reasonable number of halvings (around 64 like Bitcoin)
        if halving_count > 64:
            break
    
    # Add any remaining supply from fractional rewards
    if current_reward > 0:
        remaining_blocks = halving_interval
        remaining_supply = remaining_blocks * current_reward
        total_supply += remaining_supply
        print(f"Final Era: {current_reward:>6.2f} HMNY/block × {remaining_blocks:>6,} blocks = {remaining_supply:>12,.0f} HMNY")
    
    print("-" * 50)
    print(f"TOTAL SUPPLY: {total_supply:,.0f} HMNY")
    print()
    
    # Calculate some additional metrics
    years_to_first_halving = (halving_interval * block_time_minutes) / (365.25 * 24 * 60)
    print("Additional Metrics:")
    print(f"- First halving occurs after: {years_to_first_halving:.1f} years")
    print(f"- Total halvings: {halving_count}")
    print(f"- Final block reward: {current_reward:.8f} HMNY")
    print(f"- Supply in first 4 years: {halving_interval * initial_block_reward:,.0f} HMNY")
    
    return total_supply

if __name__ == "__main__":
    total_supply = calculate_total_supply()
