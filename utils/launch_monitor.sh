#!/bin/bash
# HashmonkeyCoin Launch Monitor
# Usage: ./launch_monitor.sh [mainnet|testnet]

set -e

NETWORK=${1:-testnet}
LOG_FILE="launch_monitor_${NETWORK}.log"
ALERT_FILE="launch_alerts_${NETWORK}.log"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to log messages
log_message() {
    echo -e "${BLUE}[$(date '+%Y-%m-%d %H:%M:%S')]${NC} $1" | tee -a "$LOG_FILE"
}

log_alert() {
    echo -e "${RED}[ALERT]${NC} $1" | tee -a "$ALERT_FILE"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1" | tee -a "$LOG_FILE"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1" | tee -a "$LOG_FILE"
}

# Function to check if daemon is running
check_daemon() {
    if pgrep -f "hashmonkeycoind.*${NETWORK}" > /dev/null; then
        return 0
    else
        return 1
    fi
}

# Function to get network info
get_network_info() {
    if check_daemon; then
        ./hashmonkeycoin-cli -${NETWORK} getnetworkinfo 2>/dev/null || echo "{}"
    else
        echo "{}"
    fi
}

# Function to get blockchain info
get_blockchain_info() {
    if check_daemon; then
        ./hashmonkeycoin-cli -${NETWORK} getblockchaininfo 2>/dev/null || echo "{}"
    else
        echo "{}"
    fi
}

# Function to get peer info
get_peer_info() {
    if check_daemon; then
        ./hashmonkeycoin-cli -${NETWORK} getpeerinfo 2>/dev/null || echo "[]"
    else
        echo "[]"
    fi
}

# Function to check system resources
check_system_resources() {
    CPU_USAGE=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)
    MEMORY_USAGE=$(free | grep Mem | awk '{printf("%.2f", $3/$2 * 100.0)}')
    DISK_USAGE=$(df / | tail -1 | awk '{print $5}' | sed 's/%//')
    
    echo "CPU: ${CPU_USAGE}%, Memory: ${MEMORY_USAGE}%, Disk: ${DISK_USAGE}%"
}

# Main monitoring loop
main() {
    log_message "Starting HashmonkeyCoin ${NETWORK} launch monitor"
    log_message "Log file: $LOG_FILE"
    log_message "Alert file: $ALERT_FILE"
    
    while true; do
        echo "=========================================="
        log_message "Network: ${NETWORK}"
        
        # Check if daemon is running
        if ! check_daemon; then
            log_alert "Daemon is not running!"
            sleep 30
            continue
        fi
        
        # Get network information
        NETWORK_INFO=$(get_network_info)
        BLOCKCHAIN_INFO=$(get_blockchain_info)
        PEER_INFO=$(get_peer_info)
        
        # Parse JSON data (requires jq)
        if command -v jq >/dev/null 2>&1; then
            # Network status
            CONNECTIONS=$(echo "$NETWORK_INFO" | jq -r '.connections // 0')
            VERSION=$(echo "$NETWORK_INFO" | jq -r '.version // 0')
            
            # Blockchain status
            BLOCKS=$(echo "$BLOCKCHAIN_INFO" | jq -r '.blocks // 0')
            HEADERS=$(echo "$BLOCKCHAIN_INFO" | jq -r '.headers // 0')
            VERIFICATION_PROGRESS=$(echo "$BLOCKCHAIN_INFO" | jq -r '.verificationprogress // 0')
            
            # Peer count
            PEER_COUNT=$(echo "$PEER_INFO" | jq length)
            
            # Log status
            log_message "Connections: $CONNECTIONS"
            log_message "Version: $VERSION"
            log_message "Blocks: $BLOCKS / $HEADERS"
            log_message "Verification Progress: $(printf "%.2f" $(echo "$VERIFICATION_PROGRESS * 100" | bc -l))%"
            log_message "Peers: $PEER_COUNT"
            
            # Alerts
            if [ "$PEER_COUNT" -lt 3 ]; then
                log_alert "Low peer count: $PEER_COUNT"
            fi
            
            if [ "$CONNECTIONS" -eq 0 ]; then
                log_alert "No network connections!"
            fi
            
            if (( $(echo "$VERIFICATION_PROGRESS < 0.99" | bc -l) )); then
                log_warning "Still syncing: $(printf "%.2f" $(echo "$VERIFICATION_PROGRESS * 100" | bc -l))%"
            else
                log_success "Fully synced!"
            fi
            
        else
            log_warning "jq not installed, showing raw data"
            echo "Network Info: $NETWORK_INFO"
            echo "Blockchain Info: $BLOCKCHAIN_INFO"
            echo "Peer Count: $(echo "$PEER_INFO" | grep -o '}' | wc -l)"
        fi
        
        # System resources
        RESOURCES=$(check_system_resources)
        log_message "System Resources: $RESOURCES"
        
        # Check for high resource usage
        CPU_USAGE=$(echo "$RESOURCES" | awk '{print $2}' | cut -d'%' -f1)
        MEMORY_USAGE=$(echo "$RESOURCES" | awk '{print $4}' | cut -d'%' -f1)
        DISK_USAGE=$(echo "$RESOURCES" | awk '{print $6}' | cut -d'%' -f1)
        
        if (( $(echo "$CPU_USAGE > 80" | bc -l) )); then
            log_warning "High CPU usage: ${CPU_USAGE}%"
        fi
        
        if (( $(echo "$MEMORY_USAGE > 80" | bc -l) )); then
            log_warning "High memory usage: ${MEMORY_USAGE}%"
        fi
        
        if [ "$DISK_USAGE" -gt 80 ]; then
            log_alert "High disk usage: ${DISK_USAGE}%"
        fi
        
        echo "=========================================="
        sleep 60
    done
}

# Handle script interruption
trap 'log_message "Monitor stopped by user"; exit 0' INT TERM

# Check if network parameter is valid
if [ "$NETWORK" != "mainnet" ] && [ "$NETWORK" != "testnet" ] && [ "$NETWORK" != "regtest" ]; then
    echo "Usage: $0 [mainnet|testnet|regtest]"
    echo "Default: testnet"
    exit 1
fi

# Start monitoring
main
