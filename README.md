# Wavefront OBJ Viewer
 
## Introduction

A simple Wavefront OBJ model viewer written in C++ using OpenGL, FreeGLUT, and SDL_image. Only the 
subset of the Wavefront OBJ specification need to render polygonal meshes is supported. All file 
references (material libraries, textures) are assumed to be relative to the *.obj file.

## Building 

You must have OpenGL, FreeGLUT, SDL_image, CMake, and a C++ compiler installed. Additionally, you must manually set the OpenGL
link directory in CMakeLists.txt (the CMake command find_package(OpenGL) is broken).

To build the project run:

*$ cmake . && make*

## Installation

To install the executable run:

*$ sudo make install*

## Usage

To view a model run:

*$ obj-viewer [-m] FILE*

where *FILE* is the path of the OBJ file. The "-m" flag turns on material properties. Many converted models do not set these values correctly, so they are turned off by default.

After running the above command, the model should then be displayed in a window. The arrow keys rotate the model, +/- zooms in and out, 'm' toggles mouse interaction, and escape quits the program.

## License

Copyright (c) 2015 James McLean  
Licensed under the MIT license.
