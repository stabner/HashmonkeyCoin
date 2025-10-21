@echo off
REM HashmonkeyCoin Advanced Build Fix Script for Windows
REM This script addresses RELIC compilation warnings and forces static builds

echo 🔧 HashmonkeyCoin Advanced Build Fix Script for Windows
echo =====================================================

REM Check if we're in the right directory
if not exist "configure.ac" (
    echo ❌ Error: Not in HashmonkeyCoin root directory
    exit /b 1
)

echo ✅ Found HashmonkeyCoin source directory

REM Apply the RELIC patch
echo 🔧 Applying RELIC build fix patch...
if exist "relic_build_fix.patch" (
    patch -p1 < relic_build_fix.patch
    echo ✅ Applied RELIC patch
) else (
    echo ⚠️  RELIC patch not found, applying manual fix...
    REM Manual fix for the SHA256Result function
    powershell -Command "(Get-Content 'src\dashbls\depends\relic\src\md\sha224-256.c') -replace 'uint8_t Message_Digest\[\]', 'uint8_t Message_Digest[SHA256HashSize]' | Set-Content 'src\dashbls\depends\relic\src\md\sha224-256.c'"
    echo ✅ Applied manual RELIC fix
)

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
    CXXFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter -Wno-unused-result" ^
    CFLAGS="-Wno-error -Wno-stringop-overflow -Wno-array-parameter -Wno-unused-result" ^
    LDFLAGS="-static-libgcc -static-libstdc++"

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
    echo    - Static linking for GCC libraries
    echo.
    echo 🔧 RELIC fixes applied:
    echo    - Fixed SHA256Result function signature
    echo    - Disabled array-parameter warnings
) else (
    echo ❌ Configuration failed!
    echo 💡 Try running this script in WSL or Linux environment
    exit /b 1
)
