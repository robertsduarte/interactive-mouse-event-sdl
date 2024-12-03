# Interactive Mouse Event (SDL2)

This project demonstrates interactive mouse events using SDL2 and SDL2_image. It works on Linux and Windows via cross-compilation using CMake (Windows binaries are generated on Linux).

## Features
- Mouse tracking with SDL2.
- Sprite rendering with SDL2_image.
- Interactive events triggered by mouse actions.

## Requirements
To build and run this project, ensure you have the following installed:

### Linux
- **SDL2 development libraries**: Install via your package manager (e.g., `libsdl2-dev` and `libsdl2-image-dev` on Ubuntu).
- **CMake**: To configure the project and generate the build system.
- **Make**: To build the project.

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev cmake make
```

### Generate Executable for Windows via Linux
- **mingw-w64**: For cross-compiling.
- **SDL2 and SDL2_image libraries**: Download the precompiled development libraries for MinGW from the SDL website:
  - https://github.com/libsdl-org/SDL/releases
  - https://github.com/libsdl-org/SDL_image/releases
  
  Extract them to a folder (e.g., ~/mingw-sdl2) and organize them as follows:
  
  ```bash
  ~/mingw-sdl2/
    SDL2.x.x.x/
      x86_64-w64-mingw32/
        include/
        lib/
    SDL2_image-x.x.x/
      x86_64-w64-mingw32/
        include/
        lib/
  ```

  - **Toolchain Configuration**: Modify the toolchain-mingw64.cmake file to point to your SDL2 and SDL2_image installation paths:
  
  ```cmake
  set(SDL2_INCLUDE_DIR /path/to/your/SDL2/include)
  set(SDL2_LIBRARY /path/to/your/SDL2/lib/libSDL2.a)
  set(SDL2_IMAGE_INCLUDE_DIR /path/to/your/SDL2_image/include)
  set(SDL2_IMAGE_LIBRARY /path/to/your/SDL2_image/lib/libSDL2_image.a)
  set(SDL2MAIN_LIBRARY /path/to/your/SDL2/lib/libSDL2main.a)
  ```

## Build Instructions

### Linux
  1. Create a `build/linux` directory:
  
  ```bash
  mkdir -p build/linux
  cd build/linux
  ```

  2. Run CMake to configure the build system:

  ```bash
  cmake ../..
  ```

  3. Compile the project:

  ```bash
  make
  ```

  4. Run the executable:

  ```bash
  ./Interactive_Mouse_Event
  ```

### Windows (Cross-Compilation)
  1. Create a `build/windows` directory:
     
  ```bash
  mkdir -p build/windows
  cd build/windows
  ```

  2. Run CMake with the toolchain file:

  ```bash
  cmake -DCMAKE_TOOLCHAIN_FILE=../../toolchain-mingw64.cmake ../..
  ```

  3. Compile the project:
  ```bash
  make
  ```
  4. Run the executable `Interactive_Mouse_Event.exe` on a Windows system.

### Notes
- Ensure the `img` folder is present in the same directory as the executable for the program to load sprites correctly.
- For cross-compilation, verify that the paths in the `toolchain-mingw64.cmake` file match your SDL2 and SDL2_image installation.
- Currently, only cross-compilation via WSL has been tested for Windows binaries.
