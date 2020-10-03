#pragma once

#include <string>
#include <vector>

namespace Utility
{

	struct Colour
	{
		float r;
		float g;
		float b;
	};

	void ParseString(const std::string& str, char token, std::vector<std::string>& buffer);
	void GetFileContents(const std::string& path, std::vector<std::string>& buffer);
	float Clamp(float value, float min, float max);

};

