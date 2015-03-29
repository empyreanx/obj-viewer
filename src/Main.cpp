#include "Viewer.hpp"
#include "ObjParser.hpp"

#include <GL/freeglut.h>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "No model specified!" << std::endl;
		return -1;
	}
	
	std::string file = std::string(argv[1]);

	ObjParser parser(file);
	
	Viewer viewer("Model Viewer", 1024, 768);
	
	ModelPtr model = parser.parseObj();
	viewer.setModel(model);
	
	viewer.initGlut(argc, argv);
	viewer.initGl();
	
	model->loadTextures();
	model->compileLists();
	
	Viewer::setInstance(&viewer);
	
	viewer.start();
	
	return 0;
}
