<p align="left">
  <img src="https://github.com/kukemanovdaniil/blocks2d/blob/main/res/logos/blocks2dfulllogo.svg" alt="Blocks2d Logo" width="500"/>
</p>

This is my pet project to create a 2D sandbox game. It runs on its own custom engine written in C++



# Latest releases
[`download`](https://github.com/kukemanovdaniil/blocks2d/releases/latest)



# Controls
| Key / Action | Description |
| :--- | :--- |
| **W \| A \| S \| D** | Player Movement |
| **R** | Change Build Mode |
| **Left Click** | Place Block |
| **Right Click** | Break Block |
| **Mouse Wheel** | Change Zoom |
| **F8** | Close Game |
| **F11** | Toggle Fullscreen |
| **Left Shift** | Sprint |



# Build
## Windows
### 1.
#### install wingw64 :
#### debian :
```bash
sudo apt install mingw-w64
```
#### arch :


```bash
cmake -B build_win_release -DCMAKE_TOOLCHAIN_FILE=win64-toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build_win_release -j4
```
### Linux
```bash
cmake -B build_lin -DCMAKE_BUILD_TYPE=Release
cmake --build build_lin -j\$(nproc)
```
