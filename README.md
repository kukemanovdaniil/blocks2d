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
| A, D | Movement |
| Space | Jump |
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
| F11 | Toggle Fullscreen |






# Screenshots

<p align="left">
  <img src="https://github.com/user-attachments/assets/f2797607-59df-4aa9-83b5-a5486101c004" "width="90%" />
  <img src="https://github.com/user-attachments/assets/d1c1b7d7-bbbe-4907-ade6-55fee51bc6ed" "width="90%" />
  <img src="https://github.com/user-attachments/assets/c7c7291d-d351-472c-b926-e97e8a3c492a" "width="90%" />
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
