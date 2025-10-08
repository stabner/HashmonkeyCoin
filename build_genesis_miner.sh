#!/bin/bash
# Build Real GhostRider Genesis Miner
# ===================================
# This script builds the real genesis miner using the actual GhostRider PoW algorithm

echo "Building Real GhostRider Genesis Miner..."
echo "========================================"

# Check if we're in the right directory
if [ ! -f "genesis_miner.cpp" ]; then
    echo "Error: genesis_miner.cpp not found. Run this from the project root."
    exit 1
fi

# Check if the project has been built
if [ ! -f "src/.libs/libhashmonkeycoinconsensus.a" ]; then
    echo "Error: Project not built yet. Please run:"
    echo "  ./autogen.sh"
    echo "  ./configure"
    echo "  make"
    exit 1
fi

# Build the genesis miner with proper linking
echo "Compiling genesis_miner.cpp with GhostRider PoW..."

g++ -std=c++17 -O2 \
    -I. -I./src -I./src/secp256k1/include -I./src/univalue/include \
    genesis_miner.cpp \
    -o genesis_miner \
    src/.libs/libhashmonkeycoinconsensus.a \
    src/secp256k1/.libs/libsecp256k1.a \
    src/univalue/.libs/libunivalue.a \
    -lssl -lcrypto -lpthread -lboost_system -lboost_filesystem

if [ $? -eq 0 ]; then
    echo "✅ Genesis miner built successfully!"
    echo "Run with: ./genesis_miner"
else
    echo "❌ Build failed. You may need to install missing dependencies:"
    echo "  sudo apt-get install libssl-dev libboost-all-dev"
fi
