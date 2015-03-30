#include "ObjParser.hpp"
#include "SmartPtr.hpp"

#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

ObjParser::ObjParser() {
}

ModelPtr ObjParser::parseObj(const std::string& fileName) {
	std::string path = filePath(fileName);
	
	ModelPtr model(new Model());
	
	std::ifstream file;
	file.open(fileName, std::ifstream::in);
	
	if (!file.is_open())
		throw std::runtime_error("Unable to open OBJ file " + fileName);
	
	std::string line;
	unsigned int groupId = 0;
	
	std::vector<MaterialPtr> materials;
	
	while(std::getline(file, line)) {
		std::stringstream sstream(line);
		
		std::string prefix;
		sstream >> prefix;
		
		if (prefix.size() > 0) {
			if ("mtllib" == prefix) {
				std::string fileName = parseFileName(prefix, line);
				materials = parseMtl(path + fileName);
			} else if ("v" == prefix) {
				model->addVertex(parseVertex(sstream));
			} else if ("vn" == prefix) {
				model->addNormal(parseNormal(sstream));
			} else if ("vt" == prefix) {
				model->addTexCoord(parseTexCoord(sstream));
			} else if ("g" == prefix) {
				std::string groupName = parseName(sstream);
				model->addGroup(parseGroup(file, groupId++, groupName, materials));
			} else {
				continue;
			}
		}
	}
	
	file.close();
	
	return model;
}

Point3 ObjParser::parseVertex(std::stringstream& sstream) {
	float x, y, z;
	
	sstream >> x >> y >> z;
	
	return Point3(x, y, z);
}

Point3 ObjParser::parseNormal(std::stringstream& sstream) {
	float x, y, z;	
	
	sstream >> x >> y >> z;
	
	return Point3(x, y, z);
}

Point2 ObjParser::parseTexCoord(std::stringstream& sstream) {
	float x, y;
	
	sstream >> x >> y;
	
	return Point2(x, 1.0 - y);
}

std::string ObjParser::parseUseMtl(const std::string& line) {
	std::stringstream sstream(line);
	
	std::string prefix;
	sstream >> prefix;
		
	if (prefix != "usemtl")
		throw std::runtime_error("Expected 'usemtl' after group declaration in file");
	
	return parseName(sstream);
}

GroupPtr ObjParser::parseGroup(std::ifstream& file, unsigned int groupId, const std::string& groupName, std::vector<MaterialPtr>& materials) {
	std::string line;
	
	if (!std::getline(file, line))
		throw std::runtime_error("OBJ file ended unexpectedly");
	
	MaterialPtr material;
	std::string materialName = parseUseMtl(line);
	
	for (unsigned int i = 0; i < materials.size(); i++) {
		if (materialName == materials[i]->name()) {
			material = materials[i];
			break;
		}
	}
	
	if (material.isNull())
		throw std::runtime_error("Unable to find material " + materialName + " referred to in OBJ file");
	
	GroupPtr group(new Group(groupId++, groupName, material));
	
	parseFaces(file, group);
	
	return group;
}

void ObjParser::parseFaces(std::ifstream& file, GroupPtr& group) {
	std::string line;
	
	while ('f' == file.peek()) {
		std::getline(file, line);
		group->addFace(parseFace(line));
	}
}

FacePtr ObjParser::parseFace(const std::string& line) {
	FacePtr face(new Face());
	
	std::stringstream sstream(line);
	std::string prefix, indexGroup;
	
	sstream >> prefix;
	
	if ("f" != prefix)
		throw std::runtime_error("Expected face definition in file");
	
	while (sstream >> indexGroup) {
		std::vector<std::string> indices = split(indexGroup, '/');
		
		if (1 == indices.size()) {
			face->addVertexIndex(stou(indices[0]));
		} else if (2 == indices.size()) {
			face->addVertexIndex(stou(indices[0]));
			face->addTexCoordIndex(stou(indices[1]));
		} else if (3 == indices.size()) {
			face->addVertexIndex(stou(indices[0]));
			face->addNormalIndex(stou(indices[2]));
			
			if ("" != indices[1])
				face->addTexCoordIndex(stou(indices[1]));
		} else {
			throw std::runtime_error("Invalid face definition in file");
		}
	}
	
	return face;
}

std::vector<MaterialPtr> ObjParser::parseMtl(const std::string& fileName) {
	std::string path = filePath(fileName);
	
	std::vector<MaterialPtr> materials;
	
	std::ifstream file;	
	file.open(fileName, std::ifstream::in);
	
	if (!file.is_open())
		throw std::runtime_error("Unable to open material library " + fileName);
	
	MaterialPtr material;
	std::string line;
	
	while(std::getline(file, line)) {
		std::stringstream sstream(line);
		
		std::string prefix;
		sstream >> prefix;
		
		float v1, v2, v3;
		
		if (prefix.size() > 0) {
			if ("newmtl" == prefix) {
				if (!material.isNull())
					materials.push_back(material);
				
				material = MaterialPtr(new Material(parseName(sstream)));
			} else if ("Ka" == prefix) {
				sstream >> v1 >> v2 >> v3;
				material->setKa(v1, v2, v3);
			} else if ("Ks" == prefix) {
				sstream >> v1 >> v2 >> v3;
				material->setKs(v1, v2, v3);
			} else if ("Kd" == prefix) {
				sstream >> v1 >> v2 >> v3;
				material->setKd(v1, v2, v3);
			} else if ("Ke" == prefix) {
				sstream >> v1 >> v2 >> v3;
				material->setKe(v1, v2, v3);
			} else if ("map_Kd" == prefix) {
				std::string fileName = parseFileName(prefix, line);
				material->setTexture(TexturePtr(new Texture(path + fileName)));
			} else {
				continue;
			}
		}
	}
		
	if (!material.isNull())
		materials.push_back(material);
	
	file.close();
	
	return materials;
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

std::string ObjParser::parseFileName(const std::string& prefix, const std::string& line) {
	return trim(line.substr(line.find(prefix) + prefix.size() + 1));
}

std::string ObjParser::filePath(const std::string& fileName) {
	size_t pos = fileName.find_last_of("/");
	
	if (std::string::npos == pos) {
		return "";
	} else
		return fileName.substr(0, pos) + "/";
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

std::string ObjParser::trim_right(const std::string& str, const std::string& delim) {
  return str.substr(0, str.find_last_not_of(delim) + 1);
}

std::string ObjParser::trim_left(const std::string& str, const std::string& delim) {
  return str.substr(str.find_first_not_of(delim));
}

std::string ObjParser::trim(const std::string& str, const std::string& delim) {
  return trim_left(trim_right(str, delim), delim);
}
