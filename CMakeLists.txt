cmake_minimum_required(VERSION 3.26)
project(Similyrically)



set(ENV{PKG_CONFIG_PATH} "C:/gtk/lib/pkgconfig")

# Use PkgConfig to find GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtkmm-4.0)

# Include GTK directories
include_directories(${GTK_INCLUDE_DIRS})

# Link GTK libraries
link_directories(${GTK_LIBRARY_DIRS})

# Add definitions (if necessary)
add_definitions(${GTK_CFLAGS_OTHER})

set(CMAKE_CXX_STANDARD 17)

add_executable(Similyrically main.cpp
        ./gui/gui.cpp
        ./gui/gui.h
        ./readresults.cpp
        ./readresults.h
        main.cpp
)

target_link_libraries(Similyrically ${GTK_LIBRARIES})
