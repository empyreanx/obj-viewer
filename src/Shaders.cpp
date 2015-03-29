#include "Shaders.hpp"

#include <GL/gl.h>

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

Shaders::Shaders(std::string vsFile, std::string fsFile) {
	std::string vsSrc = load(vsFile);
	std::string fsSrc = load(fsFile);
	
	prog_ = glCreateProgram();
	
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	
	glAttachShader(prog_, vs);
	glAttachShader(prog_, fs);
	
	const char* vsSrcPtr = vsSrc.c_str();
	const char* fsSrcPtr = fsSrc.c_str();
	
	glShaderSource(vs, 1, &vsSrcPtr, NULL);
	glShaderSource(fs, 1, &fsSrcPtr, NULL);
	
	int logLength;
	
	glCompileShader(vs);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logLength);
	
	if (logLength > 0)
		throw std::runtime_error("Error compiling shader " + vsFile);

	glCompileShader(fs);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &logLength);
	
	if (logLength > 0)
		throw std::runtime_error("Error compiling shader " + fsFile);
		
	glLinkProgram(prog_);
	glGetProgramiv(prog_, GL_INFO_LOG_LENGTH, &logLength);
	
	if (logLength > 0)
		throw std::runtime_error("Error linking shader program");
	
	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shaders::setSamplerName(std::string name) {
	samplerName_ = name;
}

bool Shaders::hasSampler() {
	return (samplerName_.size() > 0);
}

unsigned int Shaders::samplerId() {
	if (0 == samplerName_.size())
		throw std::runtime_error("Unable to get sampler ID: no sampler specified");
	
	return glGetUniformLocation(prog_, samplerName_.c_str());
}

void Shaders::use() {
	glUseProgram(prog_);
}

std::string Shaders::load(std::string filePath) {
	std::string src;
	
	std::ifstream file(filePath);
	
	if (!file.is_open())
		throw std::runtime_error("Unable to open shader file " + filePath);
		
	std::string line;
	
	while(std::getline(file, line)) {
		src += line;
	}
	
	return src;
}
