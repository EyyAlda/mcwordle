cmake_minimum_required(VERSION 3.10)

# Project configuration
project(mcwordle LANGUAGES C)

# Set C standard and compile flags
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

# Add source files for the executable
add_executable(${PROJECT_NAME} 
    src/main.c
    src/get_files_path.c
    src/gui.c
    # src/game.c
    src/gui_utility.c
    src/sqlite_handler.c
)

# Find GTK4 and GLib using PkgConfig
find_package(PkgConfig REQUIRED)
find_package(SQLite3 REQUIRED)

# Platform-specific configuration
if(WIN32)
    message(STATUS "Configuring for Windows")

    # On Windows, pkg-config may need help finding the correct paths
    # Make sure GTK4 and GLib are installed via MSYS2 and their paths are accessible

    # You may need to specify the path to MSYS2 pkg-config
    set(ENV{PKG_CONFIG_PATH} "C:/msys64/mingw64/lib/pkgconfig")

    # Find GTK4 and GLib with pkg-config
    pkg_check_modules(GTK4 REQUIRED gtk4)
    pkg_check_modules(GLIB REQUIRED glib-2.0)

    # Include GTK4 and GLib directories (MSYS2 paths)
    target_include_directories(${PROJECT_NAME}
        PRIVATE
        include/
        ${GTK4_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        
    )

    # Link GTK4 and GLib libraries (MSYS2 paths)
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE
        ${GTK4_LIBRARIES}
        ${GLIB_LIBRARIES}
        # Link Windows-specific libraries
        ws2_32 gdi32 imm32 ole32 shell32 uuid comdlg32
        SQLite::SQLite3
    )
else()
    # For Linux and other platforms
    message(STATUS "Configuring for Unix-like systems")

    # Find GTK4 and GLib with pkg-config
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
    pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)

    # Link libraries for Unix-like systems
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE
        PkgConfig::GTK4
        PkgConfig::GLIB
        SQLite::SQLite3
    )

    # Include directories for Unix-like systems
    target_include_directories(${PROJECT_NAME}
        PRIVATE
        include/
        ${GTK4_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
    )
endif()

# Add installation rules
install(TARGETS mcwordle
        RUNTIME DESTINATION bin
)

# If you have any resources (like databases, CSS, etc.), install them too
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
        DESTINATION share/mcwordle/data
        FILES_MATCHING PATTERN "*.css"
                       PATTERN "*.db"
                       PATTERN "*.png"
)

# Install desktop file if you have one
install(FILES ${CMAKE_SOURCE_DIR}/data/mcwordle.desktop
        DESTINATION share/applications
)

# Install icons if you have them
install(FILES ${CMAKE_SOURCE_DIR}/data/icons/mcwordle.png
        DESTINATION share/icons/hicolor/256x256/apps
)

# Print compiler information for debugging
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C Flags: ${CMAKE_C_FLAGS}")
