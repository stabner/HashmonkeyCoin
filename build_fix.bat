@echo off
REM HashmonkeyCoin Build Fix Script for Windows
REM This script addresses common build issues with RELIC and MinGW cross-compilation

echo 🔧 HashmonkeyCoin Build Fix Script for Windows
echo ==============================================

REM Check if we're in the right directory
if not exist "configure.ac" (
    echo ❌ Error: Not in HashmonkeyCoin root directory
    exit /b 1
)

echo ✅ Found HashmonkeyCoin source directory

REM Clean previous build artifacts
echo 🧹 Cleaning previous build artifacts...
if exist "Makefile" (
    make clean 2>nul
)

REM Remove configure script to force regeneration
if exist "configure" (
    del configure
    echo ✅ Removed old configure script
)

REM Regenerate configure script
echo 🔄 Regenerating configure script...
autogen.sh

REM Configure with static build and no warnings as errors
echo ⚙️  Configuring build with static libraries and relaxed warnings...
configure ^
    --disable-shared ^
    --enable-static ^
    --disable-werror ^
    --with-gui=qt5 ^
    CXXFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter" ^
    CFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter"

if %errorlevel% equ 0 (
    echo ✅ Configuration successful!
    echo.
    echo 🚀 You can now build with:
    echo    make -j%NUMBER_OF_PROCESSORS%
    echo.
    echo 📝 Build flags applied:
    echo    - Static libraries only (--disable-shared --enable-static)
    echo    - Warnings not treated as errors (--disable-werror)
    echo    - Relaxed compiler warnings for RELIC compatibility
) else (
    echo ❌ Configuration failed!
    echo 💡 Try running this script in WSL or Linux environment
    exit /b 1
)
