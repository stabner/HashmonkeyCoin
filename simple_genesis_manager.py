#!/usr/bin/env python3
"""
Simple Genesis Miner Manager
A simplified version that focuses on the core functionality
"""

import re
import sys
import shutil
import subprocess
import time
from pathlib import Path

ROOT = Path.cwd()
CHAINPARAMS = ROOT / "src" / "chainparams.cpp"
GEN_MINER = ROOT / "genesis_miner.cpp"

def safe_backup(p: Path):
    if not p.exists():
        return
    b = p.with_suffix(p.suffix + ".backup")
    print(f"Backing up {p} -> {b}")
    shutil.copy2(p, b)

def read_text(p: Path):
    try:
        return p.read_text(encoding="utf-8")
    except Exception as e:
        print(f"Error reading {p}: {e}")
        sys.exit(1)

def write_text(p: Path, s: str):
    try:
        p.write_text(s, encoding="utf-8")
    except Exception as e:
        print(f"Error writing {p}: {e}")
        sys.exit(1)

def analyze_current_genesis():
    """Analyze the current fake genesis blocks"""
    print("=== ANALYZING CURRENT GENESIS BLOCKS ===")
    
    if not CHAINPARAMS.exists():
        print("Error: chainparams.cpp not found!")
        return False
        
    content = read_text(CHAINPARAMS)
    
    # Find mainnet genesis block
    mainnet_match = re.search(r'genesis = CreateGenesisBlock\([^,]+,\s*[^,]+,\s*(\d+),\s*(\d+),\s*([^,]+),\s*(\d+),\s*([^)]+)\);', content)
    if mainnet_match:
        nTime, nNonce, nBits, nVersion, reward = mainnet_match.groups()
        print(f"\nMAINNET Genesis Block:")
        print(f"  nTime: {nTime}")
        print(f"  nNonce: {nNonce} <- FAKE!")
        print(f"  nBits: {nBits}")
        print(f"  nVersion: {nVersion}")
        print(f"  Reward: {reward}")
        
        if int(nNonce) < 1000:
            print(f"  WARNING: Nonce {nNonce} is suspiciously low - definitely fake!")
            return True
    
    return False

def build_genesis_miner():
    """Try to build the genesis miner"""
    print("\n=== BUILDING GENESIS MINER ===")
    
    # Try manual compilation
    cmd = [
        "g++", "-std=c++17", "-O2", "-I./src",
        "-o", "genesis_miner.exe", "genesis_miner.cpp"
    ]
    
    try:
        print("Attempting manual compilation...")
        result = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT)
        
        if result.returncode == 0:
            print("✓ Manual compilation succeeded!")
            return True
        else:
            print("Manual compilation failed:")
            print(result.stderr[:1000])
            print("\nYou may need to:")
            print("1. Install required dependencies (Boost, OpenSSL, etc.)")
            print("2. Use the project's build system")
            print("3. Build manually with proper includes")
            return False
            
    except FileNotFoundError:
        print("g++ not found. Please install a C++ compiler.")
        return False

def run_genesis_miner():
    """Run the genesis miner"""
    print("\n=== RUNNING GENESIS MINER ===")
    
    exe = ROOT / "genesis_miner.exe"
    if not exe.exists():
        print("genesis_miner.exe not found. Cannot run miner.")
        return None
    
    print("Running genesis_miner.exe...")
    print("This will mine for a proper nonce. It may take a while.")
    print("Press Ctrl+C to stop if needed.")
    print()
    
    try:
        # Run with a timeout to prevent infinite running
        result = subprocess.run([str(exe), "mainnet"], 
                              capture_output=True, text=True, timeout=300)  # 5 minute timeout
        
        if result.returncode == 0:
            print("✓ Genesis block mined successfully!")
            print("\n=== MINING RESULTS ===")
            print(result.stdout)
            return result.stdout
        else:
            print(f"✗ Mining failed: {result.stderr}")
            return None
            
    except subprocess.TimeoutExpired:
        print("✗ Mining timed out after 5 minutes")
        print("This is normal for high difficulty. Try with regtest difficulty first.")
        return None
    except KeyboardInterrupt:
        print("\n✗ Mining interrupted by user")
        return None
    except Exception as e:
        print(f"✗ Mining error: {e}")
        return None

def extract_results(output):
    """Extract mining results from output"""
    if not output:
        return None
    
    # Extract nonce, block hash, and merkle root
    nonce_match = re.search(r'nNonce:\s*(\d+)', output)
    block_hash_match = re.search(r'Block Hash:\s*([a-f0-9]+)', output)
    merkle_root_match = re.search(r'Merkle Root:\s*([a-f0-9]+)', output)
    
    if nonce_match and block_hash_match and merkle_root_match:
        return {
            'nonce': int(nonce_match.group(1)),
            'block_hash': block_hash_match.group(1),
            'merkle_root': merkle_root_match.group(1)
        }
    
    print("Could not extract all results from miner output.")
    return None

def show_manual_update_instructions(results):
    """Show manual update instructions"""
    if not results:
        return
    
    print("\n=== MANUAL UPDATE INSTRUCTIONS ===")
    print("Since automatic updating failed, please manually update chainparams.cpp:")
    print()
    print("1. Open src/chainparams.cpp")
    print("2. Find the mainnet genesis block creation line:")
    print("   genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, 1759755699, 16, 0x20001fff, 4, 500 * COIN);")
    print()
    print("3. Replace the fake nonce (16) with the mined nonce:")
    print(f"   genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, 1759755699, {results['nonce']}, 0x20001fff, 4, 500 * COIN);")
    print()
    print("4. Update the hash assertions:")
    print(f"   assert(consensus.hashGenesisBlock == uint256S(\"0x{results['block_hash']}\"));")
    print(f"   assert(genesis.hashMerkleRoot == uint256S(\"0x{results['merkle_root']}\"));")
    print()
    print("5. Save the file and rebuild the node")

def main():
    print("Simple Genesis Miner Manager")
    print("=" * 50)
    
    # Step 1: Analyze current issues
    if not analyze_current_genesis():
        print("No critical issues found.")
        return True
    
    # Step 2: Build genesis miner
    if not build_genesis_miner():
        print("Build failed. Please fix the build issues and try again.")
        return False
    
    # Step 3: Run genesis miner
    output = run_genesis_miner()
    if not output:
        print("Mining failed or timed out.")
        print("Try running with regtest difficulty first for testing.")
        return False
    
    # Step 4: Extract results
    results = extract_results(output)
    if not results:
        print("Could not extract mining results.")
        return False
    
    # Step 5: Show manual update instructions
    show_manual_update_instructions(results)
    
    print("\n" + "=" * 50)
    print("Genesis mining process completed!")
    print("Please manually update chainparams.cpp with the mined values above.")
    
    return True

if __name__ == "__main__":
    main()
