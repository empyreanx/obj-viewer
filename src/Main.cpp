#include "ObjParser.hpp"
#include "Shaders.hpp"
#include "Viewer.hpp"

#include <GL/freeglut.h>

#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Usage: obj-viewer FILE" << std::endl;
		return -1;
	}
	
	std::string fileName = std::string(argv[1]);

	ModelPtr model;
	ObjParser parser;
	
	std::cout << "Parsing model " << fileName << std::endl;
	
	try {	
		model = parser.parseObj(fileName);
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	
	Viewer viewer("Model Viewer", 1024, 768);
			
	viewer.setModel(model);
	viewer.initGlut(argc, argv);
	viewer.initGl();
	
	std::string prefix = std::string(INSTALL_PREFIX) + "/share/obj-viewer/shaders";
	std::string vsFile = prefix + "/lambertian.vs";
	std::string fsFile = prefix + "/lambertian.fs";
	
	ShadersPtr shaders(new Shaders(vsFile, fsFile));
	shaders->setSamplerName("texMap");
	
	model->loadTextures();
	model->compileLists();
	model->setShaders(shaders);
	
	Viewer::setInstance(&viewer);
	
	viewer.start();
	
	return 0;
}
