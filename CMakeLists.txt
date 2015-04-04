cmake_minimum_required(VERSION 2.8)
project(obj-viewer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find GLUT
find_package(GLUT REQUIRED)

if(NOT GLUT_FOUND)
    message(FATAL_ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

# Find OpenGL (will test using NVIDIA drivers again)
find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND OR NOT OPENGL_GLU_FOUND)
    message(FATAL_ERROR "OpenGL/GLU not found!")
endif(NOT OPENGL_FOUND OR NOT OPENGL_GLU_FOUND)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

# Find SDL
find_package(SDL REQUIRED)

if(NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif(NOT SDL_FOUND)

include_directories(${SDL_INCLUDE_DIRS})
link_directories(${SDL_LIBRARY_DIRS})
add_definitions(${SDL_DEFINITIONS})

# Find SDL
find_package(SDL_IMAGE REQUIRED)

if(NOT SDL_IMAGE_FOUND)
    message(FATAL_ERROR "SDL image library not found!")
endif(NOT SDL_IMAGE_FOUND)

include_directories(${SDL_IMAGE_INCLUDE_DIRS})
link_directories(${SDL_IMAGE_LIBRARY_DIRS})
add_definitions(${SDL_IMAGE_DEFINITIONS})

# Executable
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -DGL_GLEXT_PROTOTYPES -DINSTALL_PREFIX='\"${CMAKE_INSTALL_PREFIX}\"'")

add_executable(bin/obj-viewer "src/Arcball.cpp" "src/Viewer.cpp" "src/Model.cpp" "src/Shaders.cpp" "src/ObjParser.cpp" "src/Main.cpp")
target_link_libraries(bin/obj-viewer ${GLUT_LIBRARY} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY})

# Installation
install(TARGETS bin/obj-viewer RUNTIME DESTINATION bin)
install(DIRECTORY shaders DESTINATION share/obj-viewer)
