#ifndef _VIEWER_HPP
#define _VIEWER_HPP

#include "Model.hpp"
#include "Math/Matrix3.hpp"

#include <string>

class Viewer {
	public:
		Viewer(std::string name, int width, int height);
		virtual ~Viewer();
		
		void initGlut(int argc, char** argv);
		void initGl();
		
		void setModel(const ModelPtr& model);
		
		void start();
		void stop();
		
		void idle();
		void display();
		void resize(int width, int height);
		void keyDown(unsigned char key, int x, int y);
		void specialKey(int key, int x, int y);

		static void setInstance(Viewer* instance);
	
		static void idleCallback();
		static void displayCallback();
		static void resizeCallback(int width, int height);
		static void keyDownCallback(unsigned char key, int x, int y);
		static void specialKeyCallback(int key, int x, int y);
		
	private:
		static Viewer* instance_;
		std::string name_;
		int width_, height_;
		int windowId_;
		bool running_;
		ModelPtr model_;
		float thetaX_, thetaY_, thetaZ_;
		//Matrix3f rotation_;
		float farPlane_, modelDistance_, modelRadius_;
};



#endif
