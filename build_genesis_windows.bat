@echo off
echo HashmonkeyCoin Genesis Block Generator (Windows)
echo ===============================================
echo.

REM Check if g++ is available
g++ --version >nul 2>&1
if %errorlevel% equ 0 (
    echo ✅ g++ found. Building genesis generator...
    echo.
    
    REM Build the Windows genesis generator
    g++ -std=c++17 -o genesis_generator_windows.exe genesis_generator_windows.cpp
    
    if %errorlevel% equ 0 (
        echo ✅ Genesis generator built successfully!
        echo.
        echo Running genesis block generation...
        echo.
        
        REM Run the generator
        genesis_generator_windows.exe
    ) else (
        echo ❌ Failed to build genesis generator
    )
) else (
    echo ❌ g++ not found. Please install a C++ compiler:
    echo.
    echo Option 1: Install MinGW-w64
    echo   - Download from: https://www.mingw-w64.org/downloads/
    echo   - Or use MSYS2: https://www.msys2.org/
    echo.
    echo Option 2: Install Visual Studio Build Tools
    echo   - Download from: https://visualstudio.microsoft.com/downloads/
    echo   - Install C++ build tools
    echo.
    echo Option 3: Use WSL (Windows Subsystem for Linux)
    echo   - Install WSL2 and Ubuntu
    echo   - Run the Linux version of the genesis generator
    echo.
    echo Option 4: Use the simplified approach below
    echo.
    
    REM Provide manual values as fallback
    echo Manual Genesis Block Parameters (for testing):
    echo =============================================
    echo nTime: 1759752916
    echo nNonce: 12345 (placeholder - needs proper mining)
    echo nBits: 0x20001fff
    echo nVersion: 4
    echo genesisReward: 500 * COIN
    echo.
    echo For now, you can use these placeholder values to test the daemon startup.
    echo Later, when you have a proper build environment, generate the real genesis block.
)

echo.
echo Next Steps:
echo 1. If the generator ran successfully, copy the output values to chainparams.cpp
echo 2. If not, use the placeholder values above for testing
echo 3. Build the main HashmonkeyCoin project
echo 4. Test daemon startup with: ./hashmonkeycoind --daemon
echo 5. Generate spork keys once the daemon is running
echo.
pause
