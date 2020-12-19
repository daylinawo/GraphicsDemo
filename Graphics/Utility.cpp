#include "Utility.h"
#include <fstream>
#include <sstream>
#include <iostream>

const char HEADER_TOKEN = '[';

#define FILE_CLOSE 0x0000
#define FILE_SEARCH 0x0001
#define FILE_COPY 0x0002

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

void Utility::LoadFileContents(const std::string& path, std::string& buffer)
{
	std::ifstream file(path, std::ios_base::in);

	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			buffer += line;
		}

		file.close();
	}
}

void Utility::LoadFileContents(const std::string& path, std::string& buffer, const std::string& header)
{
	bool isHeader = false;
	uint16_t fileCommand = FILE_SEARCH;
	std::ifstream file(path, std::ios_base::in);

	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line) && fileCommand != FILE_CLOSE)
		{
			isHeader = (line[0] == HEADER_TOKEN);

			switch (fileCommand)
			{
				case FILE_SEARCH:
				{
					if (isHeader)
					{
						if (line.find(header) != std::string::npos) 
							fileCommand = FILE_COPY;
					}

					break;
				}
				case FILE_COPY:
				{
					if (isHeader)
						fileCommand = FILE_CLOSE;
					else
						buffer += line + "\n";

					break;
				}
			}
		}

		file.close();
	}
}


void Utility::LoadConfig(const std::string& path, const std::string& header, std::map<std::string, std::string>& buffer, char delim)
{
	std::string configText;

	LoadFileContents(path, configText, header);

	std::istringstream configStream(configText);
	
	std::string line;
	
	while (std::getline(configStream, line))
	{
		std::istringstream is_line(line);
		std::string key;

		if (std::getline(is_line, key, delim))
		{
			std::string value;
			if (std::getline(is_line, value))
			{
				buffer.insert({ key, value });
			}
		}
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

glm::vec3 Utility::Direction(glm::vec3 destination, glm::vec3 source)
{
	return glm::normalize(destination - source);
}

float Utility::Distance(const glm::vec3& source, const glm::vec3& destination)
{
	//1. subtract dest from source
	glm::vec3 result = source - destination;

	//2, do pythag on the result
	return sqrt((result.x * result.x) +
				(result.y * result.y) +
				(result.z * result.z));
}

void Utility::Log(const std::string& message)
{
	std::cout << message << std::endl;
}
void Utility::Log(const glm::vec3& vec)
{
	std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}
void Utility::Log(const glm::vec3& vec, const std::string& message)
{
	std::cout << message << ": " << vec.x << ", " << 
				 vec.y << ", " << vec.z << std::endl;
}
