#ifndef _MODEL_HPP
#define _MODEL_HPP

#include "Math.hpp"
#include "Shaders.hpp"
#include "SmartPtr.hpp"

#include <GL/gl.h>
#include <SDL/SDL.h>

#include <string>
#include <vector>

class Texture {
	public:
		Texture(const std::string& file);
		virtual ~Texture();
		
		void load();
		void bind();
		
	private:
		std::string file_;
		bool loaded_;
		GLuint id_;
		SDL_Surface* surface_;
};

typedef SmartPtr<Texture> TexturePtr;

class Material {
	friend class Model;
	
	public:
		Material(const std::string& name);
		Material(const Material& material);
		Material& operator = (const Material& material);

		std::string name();

		void setKa(float a1, float a2, float a3);
		void setKd(float d1, float d2, float d3);
		void setKs(float s1, float s2, float s3);
		void setKe(float e1, float e2, float e3);
		
		void setTexture(const TexturePtr& texture);
		
	private:
		std::string name_;
		float ka_[3];
		float kd_[3];
		float ks_[3];
		float ke_[3];
		TexturePtr texture_;
};

typedef SmartPtr<Material> MaterialPtr;

class Face {
	friend class Model;
	
	public:
		Face();
		
		void addVertexIndex(unsigned int index);
		void addNormalIndex(unsigned int index);
		void addTexCoordIndex(unsigned int index);
		
	private:
		std::vector<unsigned int> vertexIndices_;
		std::vector<unsigned int> normalIndices_;
		std::vector<unsigned int> texCoordIndices_;
};

typedef SmartPtr<Face> FacePtr;

class Group {
	friend class Model;
	
	public:
		Group(unsigned int id, const std::string& name, const MaterialPtr& material);
		
		void addFace(const Face& face);
		
	private:
		int id_;
		std::string name_;
		std::vector<FacePtr> faces_;
		MaterialPtr material_;
};

typedef SmartPtr<Group> GroupPtr;

class Model {
	public:
		Model();
		
		void addVertex(const Point3& vertex);
		void addNormal(const Point3& normal);
		void addTexCoord(const Point2& coord);
		
		void addGroup(const Group& group);
		
		void loadTextures();
		void compileLists();
		
		void setShaders(ShadersPtr shaders);
		
		void render();
		
	private:
		std::vector<Point3> vertices_;
		std::vector<Point3> normals_;
		std::vector<Point2> texCoords_;
		std::vector<GroupPtr> groups_;
		ShadersPtr shaders_;
};

typedef SmartPtr<Model> ModelPtr;

#endif
