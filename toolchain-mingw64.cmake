set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the cross-compiler
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Paths to SDL2 and SDL2_image
set(SDL2_INCLUDE_DIR /home/homestudio/mingw-sdl2/SDL2-2.30.9/x86_64-w64-mingw32/include/SDL2)
set(SDL2_LIBRARY /home/homestudio/mingw-sdl2/SDL2-2.30.9/x86_64-w64-mingw32/lib/libSDL2.a)
set(SDL2MAIN_LIBRARY /home/homestudio/mingw-sdl2/SDL2-2.30.9/x86_64-w64-mingw32/lib/libSDL2main.a)

set(SDL2_IMAGE_INCLUDE_DIR /home/homestudio/mingw-sdl2/SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2)
set(SDL2_IMAGE_LIBRARY /home/homestudio/mingw-sdl2/SDL2_image-2.8.2/x86_64-w64-mingw32/lib/libSDL2_image.a)