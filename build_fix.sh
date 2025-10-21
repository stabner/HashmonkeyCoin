#!/bin/bash

# HashmonkeyCoin Build Fix Script
# This script addresses common build issues with RELIC and MinGW cross-compilation

echo "🔧 HashmonkeyCoin Build Fix Script"
echo "=================================="

# Check if we're in the right directory
if [ ! -f "configure.ac" ]; then
    echo "❌ Error: Not in HashmonkeyCoin root directory"
    exit 1
fi

echo "✅ Found HashmonkeyCoin source directory"

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
    CXXFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter" \
    CFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter"

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
else
    echo "❌ Configuration failed!"
    echo "💡 Try running this script in a Linux environment or WSL"
    exit 1
fi
