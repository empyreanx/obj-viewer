#ifndef _OBJ_PARSER_HPP
#define _OBJ_PARSER_HPP

#include "Model.hpp"
#include "SmartPtr.hpp"

#include <string>
#include <vector>

class ObjParser {
	public:
		ObjParser(const std::string& file);
		
		ModelPtr parseObj();
	
	private:
		std::string file_, path_;
		std::vector<MaterialPtr> materials_;
		
		/*
		 * OBJ parsing methods
		 */
		Point3 parseVertex(std::stringstream& sstream);
		Point3 parseNormal(std::stringstream& sstream);
		Point2 parseTexCoord(std::stringstream& sstream);
		std::string parseUseMtl(const std::string& line);
		void parseFaces(std::ifstream& file, Group& group);
		Face parseFace(const std::string& line);
		
		/*
		 * Material parsing methods
		 */
		void parseMtl(const std::string& fileName);
		
		/*
		 * Utility methods
		 */
		MaterialPtr& findMaterial(const std::string& name);
		std::string parseName(std::stringstream& sstream);
		std::vector<std::string> split(const std::string& str, char delim);
		unsigned int stou(const std::string &str, size_t* idx = 0, int base = 10);
};

#endif
