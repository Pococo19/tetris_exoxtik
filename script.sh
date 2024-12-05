#!/bin/bash

# Navigate to the Raylib source directory
echo "Building Raylib..."
cd external/raylib/src || { echo "Failed to find Raylib source directory!"; exit 1; }

# Build Raylib
make PLATFORM=PLATFORM_DESKTOP || { echo "Raylib build failed!"; exit 1; }

# Return to the root directory
cd ../../../ || { echo "Failed to return to the root directory!"; exit 1; }

# Compile the project
echo "Compiling the project..."
g++ SRC/*.cpp -o tetris.exe -Iexternal/raylib/src -Lexternal/raylib/src -lraylib -lm -ldl -lpthread -lGL -lX11 || { echo "Compilation failed!"; exit 1; }

echo "Build successful! You can now run ./tetris.exe"
