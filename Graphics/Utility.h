#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <map>
#include <glm.hpp>

namespace Utility
{
	struct Colour
	{
		float r;
		float g;
		float b;
	};

	void ParseString(const std::string& str, char token, std::vector<std::string>& buffer);
	void LoadFileContents(const std::string& path, std::string& buffer);
	void LoadFileContents(const std::string& path, std::string& buffer, const std::string& header);
	void LoadConfig(const std::string& path, const std::string& header, std::map<std::string, std::string>& buffer, char delim);

	void Log(const std::string& message);
	void Log(const glm::vec3& vec);
	void Log(const glm::vec3& vec, const std::string& message);

	float Distance(const glm::vec3& source, const glm::vec3& destination);
	float Clamp(float value, float min, float max);
	glm::vec3 Direction(glm::vec3 destination, glm::vec3 source);

};

#endif
