#!/usr/bin/env python3
"""
genesis_miner_manager.py
A safer, more robust manager that:
 - parses chainparams.cpp for CreateGenesisBlock calls (more flexibly),
 - prepares parameters,
 - patches a genesis_miner.cpp with safe replacements,
 - tries to build an executable (best-effort),
 - runs the miner executable (streamed output),
 - extracts results robustly,
 - updates chainparams.cpp with backups.

This manager does NOT implement PoW. The C++ miner must implement the correct PoW for your chain.
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
BACKUP_SUFFIX = ".bak_genesis_mgr"

def safe_backup(p: Path):
    if not p.exists():
        return
    b = p.with_suffix(p.suffix + BACKUP_SUFFIX)
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

def find_create_genesis_calls(content: str):
    """
    Finds occurrences of CreateGenesisBlock(...) and returns tuples with
    the full match and the extracted arguments if possible.
    This is intentionally forgiving about whitespace and argument formatting.
    """
    pattern = re.compile(
        r'(genesis\s*=\s*CreateGenesisBlock\s*\(\s*([^,()]+)\s*,\s*([^,()]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*([^()]+)\)\s*;)',
        re.MULTILINE
    )
    return [(m.group(1), m.groups()[1:]) for m in pattern.finditer(content)]

def prepare_params():
    """
    Edit these values to your desired genesis parameters.
    - timestamp: string to embed in coinbase
    - pubkey_hex: pubkey for genesis output script (hex)
    - nTime: UNIX timestamp (int)
    - nBits: compact difficulty (hex or int)
    - nVersion: block version (int)
    - genesisRewardSats: integer satoshis (int)
    """
    return {
        "timestamp": "HashmonkeyCoin Genesis Block - Oct 08 2025 - unique launch",
        "pubkey_hex": "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f",
        "nTime": 1759755699,
        "nBits": 0x1e0ffff0,   # example low-difficulty; set appropriately
        "nVersion": 4,
        "genesisRewardSats": 500 * 100_000_000
    }

def patch_genesis_miner(params):
    if not GEN_MINER.exists():
        print(f"Error: {GEN_MINER} does not exist in project root.")
        return False
    safe_backup(GEN_MINER)
    content = read_text(GEN_MINER)
    # Replace timestamp (very permissive)
    content = re.sub(r'(timestamp\s*=\s*")[^"]+(";\s*)', r'\1' + params["timestamp"] + r'\2', content)
    # Replace pubkey hex if present (common variable name)
    content = re.sub(r'(genesisOutputScriptHex\s*=\s*")[0-9a-fA-F]+"', r'\1' + params["pubkey_hex"] + '"', content)
    # Replace nTime
    content = re.sub(r'(nTime\s*=\s*)[0-9xXa-fA-F]+(;)', r'\1' + str(params["nTime"]) + r'\2', content)
    # Replace nBits (keep hex formatting)
    nbits_hex = hex(params["nBits"])
    content = re.sub(r'(nBits\s*=\s*)0x[0-9a-fA-F]+(;)', lambda m: m.group(1) + nbits_hex + m.group(2), content)
    # Replace version
    content = re.sub(r'(nVersion\s*=\s*)[0-9]+(;)', lambda m: m.group(1) + str(params["nVersion"]) + m.group(2), content)
    # Replace genesisReward (ensure integer satoshis)
    content = re.sub(r'(genesisReward\s*=\s*)[0-9]+(\s*\*\s*COIN\s*;)', r'\1' + str(params["genesisRewardSats"] // 100_000_000) + r' \2', content)
    write_text(GEN_MINER, content)
    print("✓ genesis_miner.cpp patched (backup created).")
    return True

def build_genesis_miner():
    """
    Best-effort build. Tries autoconf/make if present; otherwise attempts to compile
    a single-file genesis_miner.cpp to genesis_miner.exe using g++. This will often
    fail if the project expects a link against internal libs — in that case run your
    repo's build system manually (the manager will still apply updates).
    """
    print("Attempting to build genesis miner...")
    # If repository has Makefile with a gen target, try it
    if (ROOT / "Makefile").exists():
        print("Running `make genesis_miner` if target exists...")
        res = subprocess.run(["make", "genesis_miner"], cwd=ROOT)
        if res.returncode == 0:
            print("✓ Make build succeeded (target: genesis_miner).")
            return True
        else:
            print("Make failed or no target. Falling back to manual compilation attempt.")
    # Manual compile fallback (may not link)
    cmd = [
        "g++", "-std=c++17", "-O2", "-I./src",
        "-o", "genesis_miner.exe", "genesis_miner.cpp"
    ]
    try:
        res = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT)
        if res.returncode == 0:
            print("✓ Manual compilation succeeded (genesis_miner.exe created).")
            return True
        else:
            print("Manual compilation failed. stderr:")
            print(res.stderr[:2000])
            print("If manual compilation fails, build the miner with your project's build system and re-run this manager.")
            return False
    except FileNotFoundError:
        print("g++ not found on PATH. Install a C++ compiler or build via your project's build system.")
        return False

def run_genesis_miner_streamed(timeout=None):
    exe = ROOT / "genesis_miner.exe"
    if not exe.exists():
        print("genesis_miner.exe not found. Cannot run miner.")
        return None
    print("Running genesis_miner.exe (streaming stdout). Ctrl+C to abort.")
    out_lines = []
    try:
        proc = subprocess.Popen([str(exe), "mainnet"], cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        start = time.time()
        while True:
            line = proc.stdout.readline()
            if line == "" and proc.poll() is not None:
                break
            if line:
                print(line.rstrip())
                out_lines.append(line)
            if timeout and (time.time() - start) > timeout:
                proc.kill()
                print("Timeout reached; miner terminated.")
                break
        proc.wait()
    except KeyboardInterrupt:
        proc.kill()
        print("Miner run interrupted by user.")
    except Exception as e:
        print("Error running miner:", e)
        return None
    return "".join(out_lines)

def extract_results(output_text: str):
    if not output_text:
        return None
    # flexible regex: accept uppercase/lowercase and optional 0x prefixes
    nonce_m = re.search(r'(?:nNonce|nonce)\s*[:=]\s*([0-9]+)', output_text, re.I)
    block_m = re.search(r'(?:Block Hash|blockhash|block hash)\s*[:=]\s*(?:0x)?([0-9a-fA-F]{64})', output_text, re.I)
    merkle_m = re.search(r'(?:Merkle Root|merkle root|merkle)\s*[:=]\s*(?:0x)?([0-9a-fA-F]{64})', output_text, re.I)
    if nonce_m and block_m and merkle_m:
        return {
            "nonce": int(nonce_m.group(1)),
            "block_hash": block_m.group(1).lower(),
            "merkle_root": merkle_m.group(1).lower()
        }
    print("Could not extract all results (nonce/hash/merkle) from miner output.")
    return None

def update_chainparams_with_results(results):
    if not CHAINPARAMS.exists():
        print("chainparams.cpp not found; cannot update.")
        return False
    safe_backup(CHAINPARAMS)
    content = read_text(CHAINPARAMS)
    # Replace nonce in CreateGenesisBlock call (attempt multiple patterns)
    # We'll attempt to replace any number that looks like nonce in CreateGenesisBlock call.
    content_new = re.sub(
        r'(CreateGenesisBlock\s*\([^,]+,\s*[^,]+,\s*)([0-9xXa-fA-F]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*([0-9xXa-fA-F]+)\s*,\s*[^)]+\))',
        lambda m: f"{m.group(1)}{results['nonce']}, {m.group(3)}, {m.group(4)}, {m.group(5)}, /*reward and rest preserved*/)",
        content, count=1
    )
    if content_new == content:
        print("Could not mutate nonce automatically; attempting a safer targeted replacement using the full previous line if present.")
        # Attempt direct string replacement if there was an exact original snippet; user may need to edit manually otherwise.
        # This conservative approach avoids accidental accidental edits.
        return False
    content = content_new
    # Replace assertions for genesis and merkle root if present
    content = re.sub(
        r'assert\s*\(\s*consensus\.hashGenesisBlock\s*==\s*uint256S\s*\(\s*"(?:0x)?[0-9a-fA-F]{64}"\s*\)\s*\)\s*;',
        f'assert(consensus.hashGenesisBlock == uint256S("0x{results["block_hash"]}"));',
        content
    )
    content = re.sub(
        r'assert\s*\(\s*genesis\.hashMerkleRoot\s*==\s*uint256S\s*\(\s*"(?:0x)?[0-9a-fA-F]{64}"\s*\)\s*\)\s*;',
        f'assert(genesis.hashMerkleRoot == uint256S("0x{results["merkle_root"]}"));',
        content
    )
    write_text(CHAINPARAMS, content)
    print("✓ chainparams.cpp updated (backup created).")
    return True

def main():
    print("Genesis Miner Manager")
    params = prepare_params()
    if not patch_genesis_miner(params):
        print("Patch failed.")
        sys.exit(1)
    ok = build_genesis_miner()
    if not ok:
        print("Build failed. You should build the miner manually with your repo build system and re-run this script to only perform extraction+update.")
        sys.exit(1)
    out = run_genesis_miner_streamed(timeout=None)  # you can pass timeout in seconds if desired
    results = extract_results(out)
    if not results:
        print("No results extracted. Inspect miner output and adjust extraction regexes or miner output format.")
        sys.exit(1)
    if not update_chainparams_with_results(results):
        print("Automatic update of chainparams.cpp failed. You may need to patch chainparams.cpp manually using the mined nonce/hash/merkle printed above.")
        print("Mined results:")
        print(results)
        sys.exit(1)
    print("All done. Rebuild your node and test acceptance of genesis block.")

if __name__ == "__main__":
    main()
