#include "ObjParser.hpp"
#include "Shaders.hpp"
#include "Viewer.hpp"

#include <GL/freeglut.h>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Usage: obj-viewer FILE" << std::endl;
		return -1;
	}
	
	std::cout << std::string(argv[0]) << std::endl;
	
	std::string file = std::string(argv[1]);

	ObjParser parser(file);
	
	Viewer viewer("Model Viewer", 1024, 768);
	
	ShadersPtr shaders = ShadersPtr(new Shaders("shaders/simple.vs", "shaders/simple.fs"));
	shaders->setSamplerName("texMap");
	
	ModelPtr model = parser.parseObj();
	viewer.setModel(model);
	
	viewer.initGlut(argc, argv);
	viewer.initGl();
	
	model->loadTextures();
	model->compileLists();
	model->setShaders(shaders);
	
	Viewer::setInstance(&viewer);
	
	viewer.start();
	
	return 0;
}
