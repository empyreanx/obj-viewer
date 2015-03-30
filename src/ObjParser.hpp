#ifndef _OBJ_PARSER_HPP
#define _OBJ_PARSER_HPP

#include "Model.hpp"
#include "SmartPtr.hpp"

#include <string>
#include <vector>

class ObjParser {
	public:
		ObjParser();
				
		ModelPtr parseObj(const std::string& fileName);
		std::vector<MaterialPtr> parseMtl(const std::string& fileName);
		
	private:
		/*
		 * OBJ parsing methods
		 */
		Point3 parseVertex(std::stringstream& sstream);
		Point3 parseNormal(std::stringstream& sstream);
		Point2 parseTexCoord(std::stringstream& sstream);
		std::string parseUseMtl(const std::string& line);
		GroupPtr parseGroup(std::ifstream& file, unsigned int groupId, const std::string& groupName, std::vector<MaterialPtr>& materials);
		void parseFaces(std::ifstream& file, GroupPtr& group);
		FacePtr parseFace(const std::string& line);
		
		/*
		 * Utility methods
		 */
		std::string parseName(std::stringstream& sstream);
		std::string parseFileName(const std::string& prefix, const std::string& line);
		std::string filePath(const std::string& fileName);
		std::vector<std::string> split(const std::string& str, char delim);
		unsigned int stou(const std::string &str, size_t* idx = 0, int base = 10);
		
		std::string trim_right(const std::string& str, const std::string& delim = " \f\n\r\t\v");
		std::string trim_left(const std::string& str, const std::string& delim = " \f\n\r\t\v");
		std::string trim(const std::string& str, const std::string& delim = " \f\n\r\t\v");
};

#endif
