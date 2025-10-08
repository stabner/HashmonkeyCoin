#!/usr/bin/env python3
"""
Simple Genesis Block Validator
Tests if the current genesis blocks in chainparams.cpp are valid
"""

import re
import subprocess
import sys
from pathlib import Path

def read_chainparams():
    """Read and parse chainparams.cpp"""
    chainparams_path = Path("src/chainparams.cpp")
    if not chainparams_path.exists():
        print("Error: src/chainparams.cpp not found!")
        return None
    
    content = chainparams_path.read_text(encoding="utf-8")
    return content

def extract_genesis_params(content):
    """Extract genesis block parameters from chainparams.cpp"""
    params = {}
    
    # Find mainnet genesis
    mainnet_match = re.search(
        r'genesis = CreateGenesisBlock\([^,]+,\s*[^,]+,\s*(\d+),\s*(\d+),\s*([^,]+),\s*(\d+),\s*([^)]+)\);',
        content
    )
    
    if mainnet_match:
        nTime, nNonce, nBits, nVersion, reward = mainnet_match.groups()
        params['mainnet'] = {
            'nTime': int(nTime),
            'nNonce': int(nNonce),
            'nBits': nBits,
            'nVersion': int(nVersion),
            'reward': reward
        }
    
    # Find testnet genesis (second occurrence)
    testnet_matches = re.findall(
        r'genesis = CreateGenesisBlock\([^,]+,\s*[^,]+,\s*(\d+),\s*(\d+),\s*([^,]+),\s*(\d+),\s*([^)]+)\);',
        content
    )
    
    if len(testnet_matches) > 1:
        nTime, nNonce, nBits, nVersion, reward = testnet_matches[1]  # Second occurrence is testnet
        params['testnet'] = {
            'nTime': int(nTime),
            'nNonce': int(nNonce),
            'nBits': nBits,
            'nVersion': int(nVersion),
            'reward': reward
        }
    
    
    return params

def check_missing_verification(content):
    """Check if VerifyGenesisPOW is missing for mainnet/testnet"""
    issues = []
    
    # Check if mainnet has VerifyGenesisPOW
    mainnet_section = re.search(r'genesis = CreateGenesisBlock\([^,]+,\s*[^,]+,\s*\d+,\s*\d+,\s*[^,]+,\s*\d+,\s*[^)]+\);\s*consensus\.hashGenesisBlock', content, re.DOTALL)
    if mainnet_section:
        section_text = mainnet_section.group(0)
        if 'VerifyGenesisPOW' not in section_text:
            issues.append("Mainnet genesis block is missing VerifyGenesisPOW(genesis) call")
    
    # Check if testnet has VerifyGenesisPOW
    testnet_section = re.search(r'genesis = CreateGenesisBlock\([^,]+,\s*[^,]+,\s*\d+,\s*\d+,\s*[^,]+,\s*\d+,\s*[^)]+\);\s*consensus\.hashGenesisBlock', content, re.DOTALL)
    if testnet_section:
        section_text = testnet_section.group(0)
        if 'VerifyGenesisPOW' not in section_text:
            issues.append("Testnet genesis block is missing VerifyGenesisPOW(genesis) call")
    
    return issues

def analyze_nonce_suspicion(params):
    """Analyze if nonces look suspicious"""
    issues = []
    
    for network, data in params.items():
        nonce = data['nNonce']
        if nonce < 1000:
            issues.append(f"{network.capitalize()} nonce {nonce} is suspiciously low - likely fake!")
        elif nonce > 1000000000:
            issues.append(f"{network.capitalize()} nonce {nonce} is suspiciously high - might be fake!")
    
    return issues

def main():
    print("Genesis Block Validator")
    print("=" * 50)
    
    # Read chainparams.cpp
    content = read_chainparams()
    if not content:
        return False
    
    # Extract parameters
    params = extract_genesis_params(content)
    if not params:
        print("Could not extract genesis parameters from chainparams.cpp")
        return False
    
    print("Current Genesis Block Configuration:")
    print("-" * 40)
    
    for network, data in params.items():
        print(f"\n{network.upper()}:")
        print(f"  nTime: {data['nTime']}")
        print(f"  nNonce: {data['nNonce']}")
        print(f"  nBits: {data['nBits']}")
        print(f"  nVersion: {data['nVersion']}")
        print(f"  Reward: {data['reward']}")
    
    # Check for issues
    print("\n" + "=" * 50)
    print("VALIDATION RESULTS:")
    print("=" * 50)
    
    issues = []
    
    # Check missing verification
    verification_issues = check_missing_verification(content)
    issues.extend(verification_issues)
    
    # Check nonce suspicion
    nonce_issues = analyze_nonce_suspicion(params)
    issues.extend(nonce_issues)
    
    if issues:
        print("ISSUES FOUND:")
        for issue in issues:
            print(f"  - {issue}")
        print("\nRECOMMENDATIONS:")
        print("  1. Add VerifyGenesisPOW(genesis) calls after genesis block creation")
        print("  2. Mine new genesis blocks with proper nonces")
        print("  3. Use the genesis_miner.cpp tool to generate valid blocks")
        return False
    else:
        print("No obvious issues found with current genesis blocks")
        print("   However, you should still verify with VerifyGenesisPOW calls")
        return True

if __name__ == "__main__":
    main()
