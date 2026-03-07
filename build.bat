@echo off
setlocal enabledelayedexpansion

:: Set VCPKG_ROOT if not already set. Default to D:\vcpkg
if "%VCPKG_ROOT%"=="" (
    set "VCPKG_ROOT=D:\vcpkg"
    echo VCPKG_ROOT not set, using default: !VCPKG_ROOT!
) else (
    echo Using VCPKG_ROOT: !VCPKG_ROOT!
)

:: Path to vcpkg executable and toolchain file
set "VCPKG_EXE=!VCPKG_ROOT!\vcpkg.exe"
set "VCPKG_TOOLCHAIN=!VCPKG_ROOT!\scripts\buildsystems\vcpkg.cmake"

:: Check if vcpkg exists
if not exist "!VCPKG_EXE!" (
    echo Error: vcpkg.exe not found at !VCPKG_EXE!
    echo Please set VCPKG_ROOT environment variable correctly.
    exit /b 1
)

:: Install dependencies
echo Installing dependencies via vcpkg...
"!VCPKG_EXE!" install boost-utility boost-circular-buffer boost-stacktrace boost-locale boost-filesystem zlib gtest fmt --triplet x64-windows
if %ERRORLEVEL% neq 0 (
    echo Error: Failed to install dependencies.
    exit /b %ERRORLEVEL%
)

:: Create build directory if it doesn't exist
if not exist "build" (
    mkdir build
)

pushd build
if %ERRORLEVEL% neq 0 (
    echo Error: Could not enter build directory.
    exit /b 1
)

:: Configure with CMake
echo Configuring project...
cmake .. ^
    -DCMAKE_TOOLCHAIN_FILE="!VCPKG_TOOLCHAIN!" ^
    -DVCPKG_TARGET_TRIPLET=x64-windows ^
    -DFMT_INSTALL=1
if %ERRORLEVEL% neq 0 (
    echo Error: CMake configuration failed.
    popd
    exit /b %ERRORLEVEL%
)

:: Build
echo Building project...
cmake --build . --config Release --verbose
if %ERRORLEVEL% neq 0 (
    echo Error: Build failed.
    popd
    exit /b %ERRORLEVEL%
)

:: Install
echo Installing...
cmake --install .
if %ERRORLEVEL% neq 0 (
    echo Error: Installation failed.
    popd
    exit /b %ERRORLEVEL%
)

echo Build and installation completed successfully.
popd
endlocal
