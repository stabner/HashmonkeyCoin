#!/bin/bash
# HashmonkeyCoin Testnet Setup Script
# This script sets up a testnet environment for development and testing

set -e

# Configuration
TESTNET_PORT=10229
TESTNET_RPC_PORT=10229
TESTNET_DATA_DIR="$HOME/.hashmonkeycoin"
TESTNET_CONF_FILE="$TESTNET_DATA_DIR/hashmonkeycoin.conf"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}HashmonkeyCoin Testnet Setup${NC}"
echo "=================================="

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to create directory if it doesn't exist
create_directory() {
    if [ ! -d "$1" ]; then
        echo -e "${YELLOW}Creating directory: $1${NC}"
        mkdir -p "$1"
    fi
}

# Function to generate random password
generate_password() {
    openssl rand -base64 32 | tr -d "=+/" | cut -c1-25
}

# Check prerequisites
echo -e "${BLUE}Checking prerequisites...${NC}"

if ! command_exists git; then
    echo "Error: git is required but not installed."
    exit 1
fi

if ! command_exists make; then
    echo "Error: make is required but not installed."
    exit 1
fi

if ! command_exists g++; then
    echo "Error: g++ is required but not installed."
    exit 1
fi

echo -e "${GREEN}Prerequisites check passed!${NC}"

# Create testnet data directory
echo -e "${BLUE}Setting up testnet data directory...${NC}"
create_directory "$TESTNET_DATA_DIR"

# Generate testnet configuration
echo -e "${BLUE}Creating testnet configuration...${NC}"

# Generate random credentials
RPC_USER="testnet_user_$(openssl rand -hex 4)"
RPC_PASSWORD=$(generate_password)

cat > "$TESTNET_CONF_FILE" << EOF
# HashmonkeyCoin Testnet Configuration
# Generated on $(date)

# Network settings
testnet=1

# RPC settings
server=1
rpcuser=$RPC_USER
rpcpassword=$RPC_PASSWORD
rpcport=$TESTNET_RPC_PORT
rpcallowip=127.0.0.1
rpcbind=127.0.0.1

# Connection settings
listen=1
maxconnections=50
maxuploadtarget=5000

# Indexing
txindex=1
addressindex=1
timestampindex=1
spentindex=1

# Logging
debug=1
logips=1

# Wallet settings
wallet=wallet.dat

# Mining settings (for testing)
gen=0
genproclimit=1

# Smartnode settings (if applicable)
smartnode=0

# Spork settings (automatic)
# No manual spork configuration needed - automatic sporks enabled
EOF

echo -e "${GREEN}Testnet configuration created: $TESTNET_CONF_FILE${NC}"

# Create testnet startup script
STARTUP_SCRIPT="$TESTNET_DATA_DIR/start_testnet.sh"
cat > "$STARTUP_SCRIPT" << 'EOF'
#!/bin/bash
# HashmonkeyCoin Testnet Startup Script

TESTNET_DATA_DIR="$HOME/.hashmonkeycoin"
CONF_FILE="$TESTNET_DATA_DIR/hashmonkeycoin.conf"

echo "Starting HashmonkeyCoin Testnet..."
echo "Data directory: $TESTNET_DATA_DIR"
echo "Configuration: $CONF_FILE"

# Check if daemon exists
if [ ! -f "./hashmonkeycoind" ]; then
    echo "Error: hashmonkeycoind not found in current directory"
    echo "Please run this script from the directory containing hashmonkeycoind"
    exit 1
fi

# Start the daemon
./hashmonkeycoind -testnet -printtoconsole -conf="$CONF_FILE"
EOF

chmod +x "$STARTUP_SCRIPT"
echo -e "${GREEN}Testnet startup script created: $STARTUP_SCRIPT${NC}"

# Create testnet CLI script
CLI_SCRIPT="$TESTNET_DATA_DIR/testnet_cli.sh"
cat > "$CLI_SCRIPT" << 'EOF'
#!/bin/bash
# HashmonkeyCoin Testnet CLI Script

TESTNET_DATA_DIR="$HOME/.hashmonkeycoin"
CONF_FILE="$TESTNET_DATA_DIR/hashmonkeycoin.conf"

# Check if CLI exists
if [ ! -f "./hashmonkeycoin-cli" ]; then
    echo "Error: hashmonkeycoin-cli not found in current directory"
    echo "Please run this script from the directory containing hashmonkeycoin-cli"
    exit 1
fi

# Pass all arguments to the CLI
./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" "$@"
EOF

chmod +x "$CLI_SCRIPT"
echo -e "${GREEN}Testnet CLI script created: $CLI_SCRIPT${NC}"

# Create testnet monitoring script
MONITOR_SCRIPT="$TESTNET_DATA_DIR/monitor_testnet.sh"
cat > "$MONITOR_SCRIPT" << 'EOF'
#!/bin/bash
# HashmonkeyCoin Testnet Monitor

TESTNET_DATA_DIR="$HOME/.hashmonkeycoin"
CONF_FILE="$TESTNET_DATA_DIR/hashmonkeycoin.conf"

echo "HashmonkeyCoin Testnet Monitor"
echo "=============================="

while true; do
    clear
    echo "$(date)"
    echo "=============================="
    
    # Check if daemon is running
    if pgrep -f "hashmonkeycoind.*testnet" > /dev/null; then
        echo -e "\033[32m✓ Daemon is running\033[0m"
        
        # Get network info
        if [ -f "./hashmonkeycoin-cli" ]; then
            echo ""
            echo "Network Information:"
            ./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" getnetworkinfo | grep -E "(connections|version)" || echo "Unable to get network info"
            
            echo ""
            echo "Blockchain Information:"
            ./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" getblockchaininfo | grep -E "(blocks|headers|verificationprogress)" || echo "Unable to get blockchain info"
            
            echo ""
            echo "Peer Information:"
            PEER_COUNT=$(./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" getpeerinfo 2>/dev/null | grep -c "}" || echo "0")
            echo "Connected peers: $PEER_COUNT"
        fi
    else
        echo -e "\033[31m✗ Daemon is not running\033[0m"
    fi
    
    echo ""
    echo "Press Ctrl+C to exit"
    sleep 10
done
EOF

chmod +x "$MONITOR_SCRIPT"
echo -e "${GREEN}Testnet monitor script created: $MONITOR_SCRIPT${NC}"

# Create testnet wallet setup script
WALLET_SCRIPT="$TESTNET_DATA_DIR/setup_wallet.sh"
cat > "$WALLET_SCRIPT" << 'EOF'
#!/bin/bash
# HashmonkeyCoin Testnet Wallet Setup

TESTNET_DATA_DIR="$HOME/.hashmonkeycoin"
CONF_FILE="$TESTNET_DATA_DIR/hashmonkeycoin.conf"

echo "Setting up HashmonkeyCoin Testnet Wallet..."
echo "=========================================="

# Check if CLI exists
if [ ! -f "./hashmonkeycoin-cli" ]; then
    echo "Error: hashmonkeycoin-cli not found in current directory"
    exit 1
fi

# Check if daemon is running
if ! pgrep -f "hashmonkeycoind.*testnet" > /dev/null; then
    echo "Error: Testnet daemon is not running"
    echo "Please start the testnet daemon first using: $TESTNET_DATA_DIR/start_testnet.sh"
    exit 1
fi

# Wait for daemon to be ready
echo "Waiting for daemon to be ready..."
sleep 5

# Create new wallet
echo "Creating new wallet..."
./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" createwallet "testnet_wallet" 2>/dev/null || echo "Wallet may already exist"

# Generate new address
echo "Generating new address..."
NEW_ADDRESS=$(./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" getnewaddress 2>/dev/null || echo "Unable to generate address")

if [ "$NEW_ADDRESS" != "Unable to generate address" ]; then
    echo "New address generated: $NEW_ADDRESS"
    echo "You can use this address to receive testnet coins"
else
    echo "Failed to generate address. Make sure the daemon is fully synced."
fi

# Show wallet info
echo ""
echo "Wallet Information:"
./hashmonkeycoin-cli -testnet -conf="$CONF_FILE" getwalletinfo | grep -E "(balance|txcount)" || echo "Unable to get wallet info"
EOF

chmod +x "$WALLET_SCRIPT"
echo -e "${GREEN}Testnet wallet setup script created: $WALLET_SCRIPT${NC}"

# Create README for testnet
README_FILE="$TESTNET_DATA_DIR/README.md"
cat > "$README_FILE" << EOF
# HashmonkeyCoin Testnet Setup

This directory contains the testnet configuration and scripts for HashmonkeyCoin.

## Files Created

- \`hashmonkeycoin.conf\` - Testnet configuration file
- \`start_testnet.sh\` - Script to start the testnet daemon
- \`testnet_cli.sh\` - Script to run CLI commands on testnet
- \`monitor_testnet.sh\` - Script to monitor testnet status
- \`setup_wallet.sh\` - Script to set up testnet wallet

## Quick Start

1. **Start the testnet daemon:**
   \`\`\`bash
   ./start_testnet.sh
   \`\`\`

2. **Monitor the testnet:**
   \`\`\`bash
   ./monitor_testnet.sh
   \`\`\`

3. **Set up wallet (in another terminal):**
   \`\`\`bash
   ./setup_wallet.sh
   \`\`\`

4. **Use CLI commands:**
   \`\`\`bash
   ./testnet_cli.sh getnetworkinfo
   ./testnet_cli.sh getblockchaininfo
   ./testnet_cli.sh getnewaddress
   \`\`\`

## Configuration

- **Network**: Testnet
- **RPC Port**: $TESTNET_RPC_PORT
- **Data Directory**: $TESTNET_DATA_DIR
- **RPC User**: $RPC_USER
- **RPC Password**: $RPC_PASSWORD

## Getting Testnet Coins

You can get testnet coins from:
- Testnet faucet (if available)
- Mining on testnet
- Other testnet users

## Important Notes

- This is a testnet environment - coins have no real value
- The blockchain will be much smaller than mainnet
- You can reset the testnet by deleting the data directory
- Automatic sporks are enabled - no manual configuration needed

## Troubleshooting

1. **Daemon won't start**: Check if port $TESTNET_PORT is available
2. **Can't connect to peers**: Wait for initial sync to complete
3. **RPC errors**: Verify the configuration file is correct
4. **Wallet issues**: Make sure the daemon is fully synced

## Support

For issues and questions:
- GitHub Issues: [HashmonkeyCoin Repository]
- Community: [Discord/Telegram channels]
- Documentation: [Project documentation]

Generated on: $(date)
EOF

echo -e "${GREEN}Testnet README created: $README_FILE${NC}"

# Final instructions
echo ""
echo -e "${GREEN}Testnet setup completed successfully!${NC}"
echo ""
echo -e "${BLUE}Next steps:${NC}"
echo "1. Build the HashmonkeyCoin binaries"
echo "2. Copy hashmonkeycoind and hashmonkeycoin-cli to this directory"
echo "3. Start the testnet: $STARTUP_SCRIPT"
echo "4. Monitor the testnet: $MONITOR_SCRIPT"
echo "5. Set up wallet: $WALLET_SCRIPT"
echo ""
echo -e "${YELLOW}Configuration file: $TESTNET_CONF_FILE${NC}"
echo -e "${YELLOW}RPC User: $RPC_USER${NC}"
echo -e "${YELLOW}RPC Password: $RPC_PASSWORD${NC}"
echo ""
echo -e "${BLUE}For more information, see: $README_FILE${NC}"
