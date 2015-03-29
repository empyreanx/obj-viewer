# Wavefront OBJ Viewer

#### Warning: Work in Progress
 
## Introduction

A Wavefront OBJ model viewer written in C++ and using OpenGL, FreeGLUT, and SDL_image.

Only the subset of the Wavefront OBJ specification need to render polygonal meshes is supported.

**Note:** All file references (material libraries, textures) are assumed to be relative to the *.obj file.

**Current Limitations:**
* Assumptions are made about the bounds of the model.
* Only one material library can be specified.
* Points are ignored.
* Many material properties are ignored.

**TODO:**
* Address limitations.
* Implement Arcball technique for mouse interaction.
* Implement anti-aliasing.
* Implement shaders.
* Make parsing more robust.

## Building 

You must have CMake and a C++ compiler installed. Additionally, you must manually set OpenGL library
link directory in CMakeLists.txt (find_package(OpenGL) is broken). To build the project run the following command:

*$ cmake . && make*

## License

Copyright (c) 2015 James McLean  
Licensed under the MIT license.
