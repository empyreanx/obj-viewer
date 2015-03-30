#include "Model.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <string>

/*
 * Texture
 */
Texture::Texture(const std::string& file) : file_(file), loaded_(false) {
}

Texture::~Texture() {
	if (loaded_) {
		glDeleteTextures(1, &id_);
		SDL_FreeSurface(surface_);
	}
}

void Texture::load() {
	if (!loaded_) {
		std::cout << "Loading texture " << file_ << std::endl;
		
		surface_ = IMG_Load(file_.c_str());

		if (NULL == surface_) {
			throw std::runtime_error("Unable to load image " + file_);
		}

		int bpp = surface_->format->BitsPerPixel;
		
		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		if (8 == bpp)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface_->w, surface_->h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, surface_->pixels);
		else if (24 == bpp)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface_->w, surface_->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface_->pixels);
		else
			throw std::runtime_error("Bits per pixel of " + std::to_string(bpp) + " not supported");
		
		loaded_ = true;
	}
}

void Texture::bind() {
	if (loaded_)
		glBindTexture(GL_TEXTURE_2D, id_);		
}

/*
 * Material
 */
Material::Material(const std::string& name) : name_(name) {
	for (int i = 0; i < 3; i++) {
		ka_[i] = 0.2f;
		kd_[i] = 0.8f;
		ks_[i] = 0.0f;
		ke_[i] = 0.0f;
	}
	
	ka_[3] = kd_[3] = ks_[3] = ke_[3] = 1.0f;
}

Material::Material(const Material& material) {
	*this = material;
}

Material& Material::operator = (const Material& material) {
	name_ = material.name_;
	
	for (int i = 0; i < 4; i++) {
		ka_[i] = material.ka_[i];
		kd_[i] = material.kd_[i];
		ks_[i] = material.ks_[i];
		ke_[i] = material.ke_[i];
	}
	
	texture_ = material.texture_;
	
	return *this;
}

std::string Material::name() const {
	return name_;
}

void Material::setKa(float a1, float a2, float a3) {
	ka_[0] = a1;
	ka_[1] = a2;
	ka_[2] = a3;
}

void Material::setKd(float d1, float d2, float d3) {
	kd_[0] = d1;
	kd_[1] = d2;
	kd_[2] = d3;
}

void Material::setKs(float s1, float s2, float s3) {
	ks_[0] = s1;
	ks_[1] = s2;
	ks_[2] = s3;
}

void Material::setKe(float e1, float e2, float e3) {
	ke_[0] = e1;
	ke_[1] = e2;
	ke_[2] = e3;
}

void Material::setTexture(const SmartPtr<Texture>& texture) {
	this->texture_ = texture;
}

/*
 * Group
 */
Group::Group(unsigned int id, const MaterialPtr& material) : id_(id), material_(material) {
}

void Group::addFace(const FacePtr& face) {
	faces_.push_back(face);
}

/*
 * Face
 */
Face::Face() {
}

Face::Face(const MaterialPtr& material) : material_(material) {
}
 
void Face::addVertexIndex(unsigned int index) {
	vertexIndices_.push_back(index);
}

void Face::addNormalIndex(unsigned int index) {
	normalIndices_.push_back(index);
}

void Face::addTexCoordIndex(unsigned int index) {
	texCoordIndices_.push_back(index);
}

/*
 * Model
 */
Model::Model() {
}

void Model::addVertex(const Point3& vertex) {
	vertices_.push_back(vertex);
}

void Model::addNormal(const Point3& normal) {
	normals_.push_back(normal);
}

void Model::addTexCoord(const Point2& coord) {
	texCoords_.push_back(coord);
}

void Model::addGroup(const GroupPtr& group) {
	groups_.push_back(group);
}

void Model::loadTextures() {
	for (unsigned int i = 0; i < groups_.size(); i++) {
		if (!groups_[i]->material_->texture_.isNull()) {
			groups_[i]->material_->texture_->load();
		}
	}
}

void Model::compileLists() {
	GLuint id = glGenLists(groups_.size());
	
	for (unsigned int i = 0; i < groups_.size(); i++) {
		GroupPtr group = groups_[i];
		
		group->id_ = id;
		
		glNewList(id, GL_COMPILE);
		
		
		for (unsigned int j = 0; j < group->faces_.size(); j++) {
			FacePtr face = group->faces_[j];
			
			glBegin(GL_POLYGON);
			
			for (unsigned int k = 0; k < face->vertexIndices_.size(); k++) {
				unsigned int index;
				
				if (face->texCoordIndices_.size() > 0) {
					index = face->texCoordIndices_[k];
					glTexCoord2fv(texCoords_[index - 1].data());
				}
				
				if (face->normalIndices_.size() > 0) {
					index = face->normalIndices_[k];
					glNormal3fv(normals_[index - 1].data());
				}
				
				index = face->vertexIndices_[k];
				glVertex3fv(vertices_[index - 1].data());
			}
			
			glEnd();
		}
		
		glEndList();
		
		id++;
	}
}

void Model::setShaders(ShadersPtr shaders) {
	shaders_ = shaders;
}

void Model::render() {
	if (!shaders_.isNull())
		shaders_->use();
	
	for (unsigned int i = 0; i < groups_.size(); i++) {
		GroupPtr group = groups_[i];
		
		MaterialPtr material = group->material_;
		
		// Disable material parameters until I have a chance to properly test and debug them.
		// Update: these calls appear to be correct, which means that the model I'm using for
		// testing was incorrectly converted from LW to OBJ.
		/*glMaterialfv(GL_FRONT, GL_AMBIENT, material->ka_);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material->kd_);
		glMaterialfv(GL_FRONT, GL_SPECULAR, material->ks_);
		glMaterialfv(GL_FRONT, GL_EMISSION, material->ke_);*/
		
		if (!material->texture_.isNull()) {
			if (!shaders_.isNull() && shaders_->hasSampler())
				glActiveTexture(GL_TEXTURE0);
			
			material->texture_->bind();
			
			if (!shaders_.isNull() && shaders_->hasSampler())
				glUniform1i(shaders_->samplerId(), 0);
		}
		
		glCallList(groups_[i]->id_);
	}
}

