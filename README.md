# Tetris
Implemented in C++ using the SFML graphics library. Replicates the original Tetris game mechanics.

<img width=500 height=800 alt="tetris-demo-gif">(https://github.com/Kevin-Duignan/Tetris/assets/109869834/b1838253-69d6-4397-a93b-dbadf38288db)</img>

 <img width=500 height=800 alt="tetris-demo-image">(https://github.com/Kevin-Duignan/Tetris/assets/109869834/bd1805b0-a321-4f5b-8c5d-d8660f6b43e9)</img>

## How to Run
    For a single-configuration generator (typically the case on Linux and macOS):
    ```
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/bin/Tetris
    ```

    For a multi-configuration generator (typically the case on Windows):
    ```
    cmake -S . -B build
    cmake --build build --config Release
    ./build/bin/Tetris
    ```
