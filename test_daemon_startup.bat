@echo off
echo Testing HashmonkeyCoin daemon startup...
echo.

set BINARY_PATH=C:\Users\thest\Desktop\HashmonkeyCoin\Hashmonkeycoin_windowsx64

echo Binary Path: %BINARY_PATH%
echo.

echo Step 1: Testing daemon startup in regtest mode...
echo Command: %BINARY_PATH%\hashmonkeycoind.exe -regtest -printtoconsole -debug=1
echo.

start "HashmonkeyCoin Regtest Debug" "%BINARY_PATH%\hashmonkeycoind.exe" -regtest -printtoconsole -debug=1

echo.
echo Daemon started. Check the window for any error messages.
echo.
echo Step 2: Waiting 10 seconds for daemon to initialize...
timeout /t 10 /nobreak > nul

echo.
echo Step 3: Checking if data directory was created...
if exist "%APPDATA%\HashmonkeyCoinCore\regtest" (
    echo SUCCESS: Data directory created at %APPDATA%\HashmonkeyCoinCore\regtest
    dir "%APPDATA%\HashmonkeyCoinCore\regtest"
) else (
    echo ERROR: Data directory NOT created at %APPDATA%\HashmonkeyCoinCore\regtest
    echo Checking if base directory exists...
    if exist "%APPDATA%\HashmonkeyCoinCore" (
        echo Base directory exists, listing contents:
        dir "%APPDATA%\HashmonkeyCoinCore"
    ) else (
        echo Base directory does not exist either
    )
)

echo.
echo Test completed. Check the daemon window for any error messages.
echo.
pause
