#!/bin/bash

# HashmonkeyCoin Advanced Build Fix Script
# This script addresses RELIC compilation warnings and forces static builds

echo "🔧 HashmonkeyCoin Advanced Build Fix Script"
echo "==========================================="

# Check if we're in the right directory
if [ ! -f "configure.ac" ]; then
    echo "❌ Error: Not in HashmonkeyCoin root directory"
    exit 1
fi

echo "✅ Found HashmonkeyCoin source directory"

# Apply the RELIC patch
echo "🔧 Applying RELIC build fix patch..."
if [ -f "relic_build_fix.patch" ]; then
    patch -p1 < relic_build_fix.patch
    echo "✅ Applied RELIC patch"
else
    echo "⚠️  RELIC patch not found, applying manual fix..."
    # Manual fix for the SHA256Result function
    sed -i 's/uint8_t Message_Digest\[\]/uint8_t Message_Digest[SHA256HashSize]/g' src/dashbls/depends/relic/src/md/sha224-256.c
    echo "✅ Applied manual RELIC fix"
fi

# Clean previous build artifacts
echo "🧹 Cleaning previous build artifacts..."
if [ -f "Makefile" ]; then
    make clean 2>/dev/null || true
fi

# Remove configure script to force regeneration
if [ -f "configure" ]; then
    rm configure
    echo "✅ Removed old configure script"
fi

# Regenerate configure script
echo "🔄 Regenerating configure script..."
./autogen.sh

# Configure with static build and no warnings as errors
echo "⚙️  Configuring build with static libraries and relaxed warnings..."
./configure \
    --disable-shared \
    --enable-static \
    --disable-werror \
    --with-gui=qt5 \
    CXXFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter -Wno-unused-result" \
    CFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter -Wno-unused-result" \
    LDFLAGS="-static-libgcc -static-libstdc++"

if [ $? -eq 0 ]; then
    echo "✅ Configuration successful!"
    echo ""
    echo "🚀 You can now build with:"
    echo "   make -j\$(nproc)"
    echo ""
    echo "📝 Build flags applied:"
    echo "   - Static libraries only (--disable-shared --enable-static)"
    echo "   - Warnings not treated as errors (--disable-werror)"
    echo "   - Relaxed compiler warnings for RELIC compatibility"
    echo "   - Static linking for GCC libraries"
    echo ""
    echo "🔧 RELIC fixes applied:"
    echo "   - Fixed SHA256Result function signature"
    echo "   - Disabled array-parameter warnings"
else
    echo "❌ Configuration failed!"
    echo "💡 Try running this script in a Linux environment or WSL"
    exit 1
fi
