#pragma once

#include <string>
#include <vector>
#include <map>

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
	float Clamp(float value, float min, float max);

	void Log(const std::string& message);
};

