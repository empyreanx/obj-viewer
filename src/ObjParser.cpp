#include "ObjParser.hpp"
#include "SmartPtr.hpp"

#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

ObjParser::ObjParser(const std::string& file) : file_(file){
	path_ = file.substr(0, file.find_last_of("/"));
}

ModelPtr ObjParser::parseObj() {
	ModelPtr model(new Model());
	
	std::string line;
	
	std::ifstream file(file_);
	
	unsigned int groupId = 0;
	
	if (file.is_open()) {
		while(std::getline(file, line)) {
			std::stringstream sstream(line);
			
			std::string prefix;
			sstream >> prefix;
			
			if (prefix.size() > 0) {
				if (prefix == "mtllib") {
					std::string fileName;
					sstream >> fileName;
					parseMtl(fileName);
				} else if (prefix == "v") {
					model->addVertex(parseVertex(line));
				} else if (prefix == "vn") {
					model->addNormal(parseNormal(line));
				} else if (prefix == "vt") {
					model->addTexCoord(parseTexCoord(line));
				} else if (prefix == "g") {
					model->addGroup(parseGroup(groupId++, line, file));
					groupId++;
				} else {
					continue;
				}
			}
		}
		
		file.close();
	}
	
	return model;
}

Point3 ObjParser::parseVertex(const std::string& line) {
	float x, y, z;	
	std::string prefix;
	
	std::stringstream sstream(line);
	
	sstream >> prefix >> x >> y >> z;
	
	return Point3(x, y, z);
}

Point3 ObjParser::parseNormal(const std::string& line) {
	float x, y, z;	
	std::string prefix;
	
	std::stringstream sstream(line);
	
	sstream >> prefix >> x >> y >> z;
	
	return Point3(x, y, z);
}

Point2 ObjParser::parseTexCoord(const std::string& line) {
	float x, y;
	std::string prefix;
	
	std::stringstream sstream(line);
	
	sstream >> prefix >> x >> y;
	
	return Point2(x, 1.0 - y);
}

Group ObjParser::parseGroup(unsigned int id, std::string line, std::ifstream& file) {
	//parse group declaration
	std::string prefix, groupName, materialName;
	
	{
		std::stringstream sstream(line);
		sstream >> prefix;
		groupName = parseName(sstream);
	}
	
	//find material declaration
	std::getline(file, line);
	
	{
		std::stringstream sstream(line);
		sstream >> prefix;
		
		if (prefix != "usemtl")
			throw std::runtime_error("Expected 'usemtl' after group declaration");
		
		materialName = parseName(sstream);
	}
	
	//create group and parse faces
	Group group(id, groupName, findMaterial(materialName));
	
	while ('f' == file.peek()) {
		std::getline(file, line);
		group.addFace(parseFace(line));
	}
	
	return group;
}

Face ObjParser::parseFace(const std::string& line) {
	Face face;
	
	std::stringstream sstream(line);
	std::string prefix, indexGroup;
	
	sstream >> prefix;
	
	while (sstream >> indexGroup) {
		std::vector<std::string> indices = split(indexGroup, '/');
		
		if (1 == indices.size()) {
			face.addVertexIndex(stou(indices[0]));
		} else if (2 == indices.size()) {
			face.addVertexIndex(stou(indices[0]));
			face.addTexCoordIndex(stou(indices[1]));
		} else if (3 == indices.size()) {
			face.addVertexIndex(stou(indices[0]));
			face.addNormalIndex(stou(indices[2]));
			
			if ("" != indices[1])
				face.addTexCoordIndex(stou(indices[1]));
		} else {
			throw std::runtime_error("Invalid face definition");
		}
	}
	
	return face;
}

void ObjParser::parseMtl(const std::string& fileName) {
	std::string line;
	
	std::ifstream file(path_ + "/" + fileName);
	
	MaterialPtr material;
	
	if (file.is_open()) {
		while(std::getline(file, line)) {
			std::stringstream sstream(line);
			
			std::string prefix;
			sstream >> prefix;
			
			if (prefix.size() > 0) {
				if (prefix == "newmtl") {
					if (!material.isNull())
						materials_.push_back(material);
					
					material = MaterialPtr(new Material(parseName(sstream)));					
				} else if (prefix == "Ka") {
					float v1, v2, v3;
					sstream >> v1 >> v2 >> v3;
					material->setKa(v1, v2, v3);
				} else if (prefix == "Ks") {
					float v1, v2, v3;
					sstream >> v1 >> v2 >> v3;
					material->setKs(v1, v2, v3);
				} else if (prefix == "Kd") {
					float v1, v2, v3;
					sstream >> v1 >> v2 >> v3;
					material->setKd(v1, v2, v3);
				} else if (prefix == "Ke") {
					float v1, v2, v3;
					sstream >> v1 >> v2 >> v3;
					material->setKe(v1, v2, v3);
				} else if (prefix == "map_Kd") {
					std::string fileName;
					sstream >> fileName;
					material->setTexture(TexturePtr(new Texture(path_ + "/" + fileName)));
				} else {
					continue;
				}
			}
		}
		
		if (!material.isNull())
			materials_.push_back(material);
		
		file.close();
	} else {
		throw std::runtime_error("Unable to open material library " + fileName);
	}
}

MaterialPtr& ObjParser::findMaterial(const std::string& name) {
	for (unsigned int i = 0; i < materials_.size(); i++) {
		if (materials_[i]->name() == name)
			return materials_[i];
	}
	
	throw std::runtime_error("Material " + name + " was not found!");
}

std::string ObjParser::parseName(std::stringstream& sstream) {
	std::string name, word;
	
	while (sstream >> word) {
		if (0 == name.size())
			name += word;
		else
			name += " " + word;
	}
	
	return name;
}

std::vector<std::string> ObjParser::split(const std::string& str, char delim) {
	std::vector<std::string> items;
	std::stringstream sstream(str);
	std::string item;
	
	while (std::getline(sstream, item, delim))
		items.push_back(item);
		
	return items;
}

unsigned int ObjParser::stou(const std::string &str, size_t* idx, int base) {
    unsigned long result = std::stoul(str, idx, base);
    
    if (result > std::numeric_limits<unsigned>::max()) {
        throw std::out_of_range("stou");
    }
    
    return result;
}
