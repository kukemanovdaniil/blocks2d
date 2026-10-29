</p>
  <img alt="blocks2dfulllogo" src="https://github.com/user-attachments/assets/a9f68815-0c72-445f-909b-f4184e3d6106" /><p align="center">
</p>

---

> 2D sandbox game. It runs on its own custom engine written in C++






# About Project

**Blocks2D** is an open-source 2D sandbox game built entirely on a custom, lightweight engine written from scratch in C++

The project started and continues to thrive as a personal endeavor, driven by two core goals
* **Learning & Experimentation :** Serving as a hands on playground for advanced C++ architecture, engine design, and graphics rendering
* **Community Asset :** Creating a solid, accessible base game that others can enjoy playing, modding, or using for their own educational and development purposes






# Installation

### Binaries (Latest Release)

* **[`Download`](https://github.com/kukemanovdaniil/blocks2d/releases/latest)**

---

### Source

* **From Git (Terminal)**
  ```sh
  git clone https://github.com/kukemanovdaniil/blocks2d
  cd blocks2d
  ```

* **From GitHub (Web)**
  * Click on the green **"Code"** button at the top of this repository webpage
  * Select **"Download ZIP"** from the dropdown menu and unpack the archive






# Controls

### Movement
| Key / Action | Description |
| :--- | :--- |
| W, A, S, D | Player Movement |
| Left Shift | Sprint |

### Camera
| Key / Action | Description |
| :--- | :--- |
| Mouse Wheel | Change Zoom |

### Gameplay Action
| Key / Action | Description |
| :--- | :--- |
| R | Change Build Mode |
| Left Click | Place Block |
| Right Click | Break Block |

### Hotkeys
| Key / Action | Description |
| :--- | :--- |
| F8 | Close Game |
| F11 | Toggle Fullscreen |






# Screenshots

<p align="left">
  <img src="https://github.com/user-attachments/assets/004aaef5-e539-4364-b089-2ecd43d8e52b "width="90%" />
  <img src="https://github.com/user-attachments/assets/9e286f6b-b6f8-4a4b-a2cb-66e15f524a92" width="90%" />
  <img src="https://github.com/user-attachments/assets/4e99b83f-3797-4c72-9c18-0151f846f005" width="90%" />
  
</p>






# Build

### Linux (native)
```sh
cmake -B build_linux -DCMAKE_BUILD_TYPE=Release
cmake --build build_linux -j$(nproc)
```

---

### Cross-Compile Windows (Linux)

#### 1. Install MinGW

* **Debian**
  ```sh
  sudo apt install -y mingw-w64
  ```
* **Arch**
  ```sh
  sudo pacman -Syu --noconfirm x86_64-w64-mingw32-gcc
  ```
* **Fedora**
  ```sh
  sudo dnf install -y mingw64-gcc mingw64-gcc-c++
  ```

#### 2. Compile
```sh
cmake -B build_windows -DCMAKE_TOOLCHAIN_FILE=win64-toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build_windows -j$(nproc)
```

---

### Windows (native)
```sh
none, its placeholder
```

---

### Cross-Compile Linux (Windows)
```sh
none, its placeholder
```
