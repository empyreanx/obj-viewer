# Wavefront OBJ Viewer

#### Work in Progress
 
## Introduction

A simple Wavefront OBJ model viewer written in C++ using OpenGL, FreeGLUT, and SDL_image.

**Note:** Only the subset of the Wavefront OBJ specification need to render polygonal meshes is supported.

**Note:** All file references (material libraries, textures) are assumed to be relative to the *.obj file.

**Current Limitations:**
* Assumptions are made about the bounds of the model.
* Points are ignored.
* Many material properties are ignored.

**TODO:**
* Address limitations.
* Implement Arcball technique for mouse interaction.
* Implement anti-aliasing.
* Implement better shaders.
* Make parsing more robust.

## Building 

You must have OpenGL, FreeGLUT, SDL_image, CMake, and a C++ compiler installed. Additionally, you must manually set the OpenGL
link directory in CMakeLists.txt (find_package(OpenGL) is broken).

To build the project run the following command:

*$ cmake . && make*

## Usage

To view a model, enter the following command:

*$ bin/obj-viewer FILE*

where *FILE* is the path of the OBJ file. You must run this command from the project directory in order for the shaders to be found.

The model should then be displayed in a window. Use the arrow keys rotate the model. Escape quits the program.

## License

Copyright (c) 2015 James McLean  
Licensed under the MIT license.
