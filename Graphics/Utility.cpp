#include "Utility.h"
#include <fstream>

void Utility::ParseString(const std::string& str, char token, std::vector<std::string>& buffer)
{
	std::string tempStr;

	for (auto it = str.begin(); it != str.end(); it++)
	{
		if ((*it) == token)
		{
			if (!tempStr.empty())
			{
				buffer.push_back(tempStr);
				tempStr.clear();
			}

			continue;
		}

		tempStr += *it;
	}

	if (!tempStr.empty())
	{
		buffer.push_back(tempStr);
		tempStr.clear();
	}

}

void Utility::GetFileContents(const std::string& path, std::vector<std::string>& buffer)
{
	std::ifstream file(path, std::ios_base::in);

	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			buffer.push_back(line);
		}

		file.close();
	}
}

float Utility::Clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}
	else if (value > max)
	{
		return max;
	}

	return value;
}
