#!/usr/bin/env python3
"""
HashmonkeyCoin Genesis Block Miner
This script mines the genesis block and provides the correct values for chainparams.cpp
"""

import hashlib
import struct
import time

# Genesis block parameters
GENESIS_TIME = 1755295200  # August 16, 2025
GENESIS_BITS = 0x20001fff
GENESIS_VERSION = 4
GENESIS_REWARD = 50000000000  # 500 HMNY in satoshis

# Genesis message
GENESIS_MESSAGE = "The Times 16/Aug/2025 HashmonkeyCoin - The Future of Decentralized Finance"

# Genesis output script (from chainparams.cpp)
GENESIS_OUTPUT_SCRIPT = bytes.fromhex("41040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b179c45070ac7b03a9ac")

def double_sha256(data):
    """Perform double SHA256 hashing"""
    return hashlib.sha256(hashlib.sha256(data).digest()).digest()

def create_genesis_transaction():
    """Create the genesis transaction"""
    # Version
    tx = struct.pack("<I", 1)
    
    # Input count
    tx += b'\x01'
    
    # Input
    # Previous output hash (null)
    tx += b'\x00' * 32
    # Previous output index
    tx += struct.pack("<I", 0xffffffff)
    
    # Script length
    script_sig = b'\x04' + struct.pack("<I", 0x1d00ffff) + b'\x01' + struct.pack("<B", len(GENESIS_MESSAGE)) + GENESIS_MESSAGE.encode()
    tx += struct.pack("<B", len(script_sig))
    tx += script_sig
    
    # Sequence
    tx += struct.pack("<I", 0xffffffff)
    
    # Output count
    tx += b'\x01'
    
    # Output
    # Value (500 HMNY in satoshis)
    tx += struct.pack("<Q", GENESIS_REWARD)
    
    # Script length
    tx += struct.pack("<B", len(GENESIS_OUTPUT_SCRIPT))
    tx += GENESIS_OUTPUT_SCRIPT
    
    # Lock time
    tx += struct.pack("<I", 0)
    
    return tx

def create_block_header(merkle_root, nonce):
    """Create block header"""
    header = struct.pack("<I", GENESIS_VERSION)  # Version
    header += b'\x00' * 32  # Previous block hash (null)
    header += merkle_root  # Merkle root
    header += struct.pack("<I", GENESIS_TIME)  # Timestamp
    header += struct.pack("<I", GENESIS_BITS)  # Bits
    header += struct.pack("<I", nonce)  # Nonce
    return header

def check_target(hash_bytes, target_bits):
    """Check if hash meets target"""
    target = (target_bits & 0x007fffff) << (8 * ((target_bits >> 24) - 3))
    
    # Convert hash to integer (little-endian)
    hash_int = int.from_bytes(hash_bytes, byteorder='little')
    
    return hash_int < target

def main():
    print("=== HashmonkeyCoin Genesis Block Miner ===")
    print(f"Timestamp: {GENESIS_TIME} (August 16, 2025)")
    print(f"Bits: 0x{GENESIS_BITS:08x}")
    print(f"Reward: 500 HMNY")
    print(f"Message: {GENESIS_MESSAGE}")
    print()
    
    # Create genesis transaction
    genesis_tx = create_genesis_transaction()
    print(f"Genesis Transaction: {genesis_tx.hex()}")
    
    # Calculate merkle root
    merkle_root = double_sha256(genesis_tx)
    print(f"Merkle Root: {merkle_root.hex()}")
    print()
    
    # Mine the genesis block
    print("Mining genesis block...")
    start_time = time.time()
    
    nonce = 0
    while nonce < 0xffffffff:
        # Create block header
        header = create_block_header(merkle_root, nonce)
        
        # Calculate block hash
        block_hash = double_sha256(header)
        
        # Check if hash meets target
        if check_target(block_hash, GENESIS_BITS):
            elapsed = time.time() - start_time
            print(f"Genesis block found!")
            print(f"Nonce: {nonce}")
            print(f"Block Hash: {block_hash.hex()}")
            print(f"Merkle Root: {merkle_root.hex()}")
            print(f"Time taken: {elapsed:.2f} seconds")
            print()
            
            # Output values for chainparams.cpp
            print("=== Genesis Block Values for chainparams.cpp ===")
            print("// Replace the TODO comments with:")
            print(f'assert(consensus.hashGenesisBlock == uint256S("0x{block_hash.hex()}"));')
            print(f'assert(genesis.hashMerkleRoot == uint256S("0x{merkle_root.hex()}"));')
            print("// And update the nonce in CreateGenesisBlock call:")
            print(f"genesis = CreateGenesisBlock({GENESIS_TIME}, {nonce}, 0x{GENESIS_BITS:08x}, {GENESIS_VERSION}, 500 * COIN);")
            break
        
        nonce += 1
        if nonce % 1000000 == 0:
            elapsed = time.time() - start_time
            rate = nonce / elapsed
            print(f"Tried nonce: {nonce:,} (Rate: {rate:,.0f} hashes/sec)")
    
    if nonce >= 0xffffffff:
        print("Failed to find valid genesis block!")
        return 1
    
    return 0

if __name__ == "__main__":
    main()
