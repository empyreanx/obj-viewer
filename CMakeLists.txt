cmake_minimum_required(VERSION 2.8)
project(obj-viewer)

# Find GLUT
find_package(GLUT REQUIRED)

if(NOT GLUT_FOUND)
    message(FATAL_ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

# This section is not finding the appropriate OpenGL causing a link error assertion.
# See below for the workaround.
# Find OpenGL
#find_package(OpenGL REQUIRED)

#if(NOT OPENGL_FOUND)
#    message(FATAL_ERROR "OpenGL not found!")
#endif(NOT OPENGL_FOUND)

#include_directories(${OpenGL_INCLUDE_DIRS})
#link_directories(${OpenGL_LIBRARY_DIRS})
#add_definitions(${OpenGL_DEFINITIONS})

#

# Here is the workaround. Adjust it accordingly for your system
link_directories("/usr/lib/nvidia-331-updates")

# Executable
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_executable(bin/obj-viewer "src/Viewer.cpp" "src/Math.cpp" "src/Model.cpp" "src/ObjParser.cpp" "src/Main.cpp")
target_link_libraries(bin/obj-viewer ${GLUT_LIBRARY} "GL" "GLU" "SDL_image" "SDL")
