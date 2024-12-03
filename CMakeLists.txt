cmake_minimum_required(VERSION 3.10)
project(Interactive_Mouse_Event C)

# Add the executable target
add_executable(Interactive_Mouse_Event main.c)

# Platform-specific settings
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Include SDL2 and SDL2_image directories
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
    
    # Link SDL2 and SDL2_image static libraries
    target_link_libraries(Interactive_Mouse_Event
        mingw32                # Needed for SDL's WinMain entry point
        ${SDL2MAIN_LIBRARY}    # SDL2main library
        ${SDL2_LIBRARY}        # SDL2 library
        ${SDL2_IMAGE_LIBRARY}  # SDL2_image library
        m                      # Math library
        setupapi               # Device installation functions
        imm32                  # Input method management
        version                # Version info functions
        winmm                  # Multimedia functions
    )
else()
    # Linux-specific configuration
    find_package(SDL2 REQUIRED)
    find_library(SDL2_IMAGE_LIBRARIES SDL2_image REQUIRED)

    # Add SDL2 include directories
    include_directories(${SDL2_INCLUDE_DIRS})

    # Set SDL2 and SDL2_image libraries for Linux
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES})

    # Link SDL2 and SDL2_image libraries for Linux
    target_link_libraries(Interactive_Mouse_Event 
        ${SDL2_LIBRARIES} 
        ${SDL2_IMAGE_LIBRARIES} 
        m # Math library
    )
endif()

# Copy "img" folder to the build directory after build
add_custom_command(
    TARGET Interactive_Mouse_Event POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/img
    $<TARGET_FILE_DIR:Interactive_Mouse_Event>/img
)