#include "Viewer.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <iostream>

Viewer* Viewer::instance_ = NULL;

Viewer::Viewer(std::string name, int width, int height) : name_(name), width_(width), 
	height_(height), running_(false), thetaX_(0.0f), thetaY_(0.0f) {
}

Viewer::~Viewer() {
}

void Viewer::initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(width_, height_);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width_) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height_) / 2);
	glutCreateWindow(name_.c_str());
}

void Viewer::initGl() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
		
	glCullFace(GL_BACK);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);	
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    gluPerspective(45.0f, (GLfloat)width_/(GLfloat)height_, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void Viewer::setModel(const SmartPtr<Model>& model) {
	model_ = model;
}

void Viewer::start() {
	if (!running_) {
		running_ = true;
		glutMainLoop();
	}
}

void Viewer::stop() {
	if (running_)
		glutLeaveMainLoop();
}

void Viewer::idle() {
	glutPostRedisplay();
}

void Viewer::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(thetaX_, 1.0f, 0.0f, 0.0f);
	glRotatef(thetaY_, 0.0f, 1.0f, 0.0f);
	
	model_->render();
	
	glutSwapBuffers();
}

void Viewer::resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    gluPerspective(45.0f, (GLfloat)width_/(GLfloat)height_, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Viewer::keyDown(unsigned char key, int x, int y) {
	if (27 == key) {
		stop();
	}
}

void Viewer::specialKey(int key, int x, int y) {
	switch(key)	{
		case GLUT_KEY_UP:
			thetaX_ += 5.0f;
			break;

		case GLUT_KEY_DOWN:
			thetaX_ -= 5.0f;
			break;
		
		case GLUT_KEY_LEFT:
			thetaY_ -= 5.0f;
			break;
		
		case GLUT_KEY_RIGHT:
			thetaY_ += 5.0f;
			break;
	}
}

/*
 * Static callbacks
 */
void Viewer::setInstance(Viewer* instance) {
	instance_ = instance;
	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyDownCallback);
	glutSpecialFunc(specialKeyCallback);
}

void Viewer::idleCallback() {
	instance_->idle();
}

void Viewer::displayCallback() {
	instance_->display();
}

void Viewer::resizeCallback(int width, int height) {
	instance_->resize(width, height);
}

void Viewer::keyDownCallback(unsigned char key, int x, int y) {
	instance_->keyDown(key, x, y);
}

void Viewer::specialKeyCallback(int key, int x, int y) {
	instance_->specialKey(key, x, y);
}
