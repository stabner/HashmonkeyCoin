#!/bin/bash
# Script to replace remaining Raptoreum references in RPC help text
# This handles the less critical references in help documentation

cd "$(dirname "$0")/src"

# Replace in RPC help text (less critical but good to update)
find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/raptoreum address/hashmonkeycoin address/g' {} \;
find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/Raptoreum address/HashmonkeyCoin address/g' {} \;
find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/raptoreumd/hashmonkeycoind/g' {} \;

echo "Replaced remaining Raptoreum references in RPC help text"

