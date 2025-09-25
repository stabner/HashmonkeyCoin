#!/bin/bash

# HashmonkeyCoin Branding Replacement Script
# This script performs comprehensive branding replacement across the codebase

echo "Starting comprehensive branding replacement..."

# Function to replace in files
replace_in_files() {
    local pattern="$1"
    local replacement="$2"
    local description="$3"
    
    echo "Replacing: $description"
    find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.md" -o -name "*.txt" -o -name "*.sh" -o -name "*.py" -o -name "*.ac" -o -name "*.am" -o -name "*.ui" -o -name "*.ts" -o -name "*.xlf" -o -name "*.java" -o -name "*.xml" -o -name "*.json" -o -name "*.rc" \) -exec sed -i "s/$pattern/$replacement/g" {} \;
}

# Core branding replacements
replace_in_files "HashmonkeyCoin Core" "HashmonkeyCoin Core" "HashmonkeyCoin Core -> HashmonkeyCoin Core"
replace_in_files "Raptoreum" "HashmonkeyCoin" "Raptoreum -> HashmonkeyCoin"
replace_in_files "raptoreum" "hashmonkeycoin" "raptoreum -> hashmonkeycoin"
replace_in_files "RTM" "HMNY" "RTM -> HMNY"
replace_in_files "rtm" "hmny" "rtm -> hmny"

# Executable names
replace_in_files "hashmonkeycoind" "hashmonkeycoind" "hashmonkeycoind -> hashmonkeycoind"
replace_in_files "hashmonkeycoin-qt" "hashmonkeycoin-qt" "hashmonkeycoin-qt -> hashmonkeycoin-qt"
replace_in_files "hashmonkeycoin-cli" "hashmonkeycoin-cli" "hashmonkeycoin-cli -> hashmonkeycoin-cli"
replace_in_files "hashmonkeycoin-wallet" "hashmonkeycoin-wallet" "hashmonkeycoin-wallet -> hashmonkeycoin-wallet"

# Configuration files
replace_in_files "hashmonkeycoin-config.h" "hashmonkeycoin-config.h" "config header file"
replace_in_files "hashmonkeycoin.conf" "hashmonkeycoin.conf" "config file name"

# URLs and repositories
replace_in_files "https://github.com/Raptor3um/raptoreum" "https://github.com/stabner/HashmonkeyCoin" "repository URL"
replace_in_files "https://raptoreum.com" "https://hashmonkeycoin.com" "website URL"

# Package names
replace_in_files "raptoreumcore" "hashmonkeycoin" "package name"

echo "Branding replacement completed!"
echo "Please review the changes and test the build."
