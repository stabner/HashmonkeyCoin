#!/bin/bash
# Script to prepare for mining new genesis blocks with GhostRiderV2

set -e

echo "=========================================="
echo "HashmonkeyCoin Genesis Block Mining Prep"
echo "=========================================="
echo ""

# Get current timestamp
CURRENT_TIMESTAMP=$(date +%s)
CURRENT_DATE=$(date -u +"%Y-%m-%d %H:%M:%S UTC")

echo "Current timestamp: $CURRENT_TIMESTAMP"
echo "Current date: $CURRENT_DATE"
echo ""

# Calculate timestamps for each network
MAINNET_TS=$CURRENT_TIMESTAMP
TESTNET_TS=$((CURRENT_TIMESTAMP + 1))
REGTEST_TS=$((CURRENT_TIMESTAMP + 2))

echo "Recommended timestamps:"
echo "  Mainnet:  $MAINNET_TS"
echo "  Testnet:  $TESTNET_TS"
echo "  Regtest:  $REGTEST_TS"
echo ""

# Backup chainparams.cpp
if [ ! -f "src/chainparams.cpp.backup" ]; then
    echo "Creating backup of chainparams.cpp..."
    cp src/chainparams.cpp src/chainparams.cpp.backup
    echo "✓ Backup created: src/chainparams.cpp.backup"
else
    echo "⚠ Backup already exists: src/chainparams.cpp.backup"
fi

echo ""
echo "=========================================="
echo "Next Steps:"
echo "=========================================="
echo ""
echo "1. Update timestamps in src/chainparams.cpp:"
echo "   - Mainnet:  CreateGenesisBlock($MAINNET_TS, ...)"
echo "   - Testnet:  CreateTestnetGenesisBlock($TESTNET_TS, ...)"
echo "   - Regtest:  CreateRegtestGenesisBlock($REGTEST_TS, ...)"
echo ""
echo "2. Comment out the assert statements for genesis hash verification"
echo "   (temporarily, so the daemon can find new valid nonces)"
echo ""
echo "3. Build the daemon:"
echo "   ./autogen.sh"
echo "   ./configure"
echo "   make"
echo ""
echo "4. Run the daemon - it will automatically find valid nonces:"
echo "   ./src/hashmonkeycoind -regtest"
echo "   (Check logs for genesis block hash and merkle root)"
echo ""
echo "5. Update chainparams.cpp with the new genesis hashes"
echo ""
echo "6. Uncomment the assert statements"
echo ""
echo "=========================================="

