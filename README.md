<p align="center">
  <img src="https://github.com/kukemanovdaniil/blocks2d/blob/main/res/logos/blocks2dfulllogo.svg" alt="Blocks2d Logo" width="700"/>
</p>

<h3 align="center">
  This is my pet project to create a 2D sandbox game. <br/>
  It runs on its own custom engine written in C++
</h3>

---

# Latest releases
[`download`](https://github.com/kukemanovdaniil/blocks2d/releases/latest)



# Controls

### Movement
| Key / Action | Description |
| :--- | :--- |
| **W \| A \| S \| D** | Player Movement |
| **Left Shift** | Sprint |

### Camera
| Key / Action | Description |
| :--- | :--- |
| **Mouse Wheel** | Change Zoom |

### Gameplay Action
| Key / Action | Description |
| :--- | :--- |
| **R** | Change Build Mode |
| **Left Click** | Place Block |
| **Right Click** | Break Block |

### Hotkeys
| Key / Action | Description |
| :--- | :--- |
| **F8** | Close Game |
| **F11** | Toggle Fullscreen |




# Build

### Linux
```bash
cmake -B build_linux -DCMAKE_BUILD_TYPE=Release
cmake --build build_linux -j$(nproc)
```

---

### Windows
To cross-compile for Windows from Linux, you need to install **MinGW** first.

#### 1. Install MinGW

* **Debian**
  ```bash
  sudo apt install -y mingw-w64
  ```
* **Arch**
  ```bash
  sudo pacman -Syu --noconfirm x86_64-w64-mingw32-gcc
  ```
* **Fedora**
  ```bash
  sudo dnf install -y mingw64-gcc mingw64-gcc-c++
  ```

#### 2. Compile
```bash
cmake -B build_windows -DCMAKE_TOOLCHAIN_FILE=win64-toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build_windows -j$(nproc)
```

