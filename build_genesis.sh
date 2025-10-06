#!/bin/bash

echo "Building HashmonkeyCoin Genesis Block Generator"
echo "=============================================="

cd src

echo "Building mainnet genesis generator..."
g++ -std=c++17 -I. -I./secp256k1/include -I./univalue/include -I./leveldb/include -I./crypto \
    genesis_generator.cpp -o genesis_generator

if [ $? -eq 0 ]; then
    echo "✅ Mainnet genesis generator built successfully!"
    echo "Run: ./genesis_generator"
else
    echo "❌ Failed to build mainnet genesis generator"
fi

echo ""
echo "Building testnet genesis generator..."
g++ -std=c++17 -I. -I./secp256k1/include -I./univalue/include -I./leveldb/include -I./crypto \
    genesis_generator_testnet.cpp -o genesis_generator_testnet

if [ $? -eq 0 ]; then
    echo "✅ Testnet genesis generator built successfully!"
    echo "Run: ./genesis_generator_testnet"
else
    echo "❌ Failed to build testnet genesis generator"
fi

echo ""
echo "Instructions:"
echo "1. Run ./genesis_generator to mine mainnet genesis block"
echo "2. Run ./genesis_generator_testnet to mine testnet genesis block"
echo "3. Copy the output values to chainparams.cpp"
echo "4. Rebuild the main project"
