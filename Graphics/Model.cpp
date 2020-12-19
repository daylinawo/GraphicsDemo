#include <fstream>
#include <iostream>
#include <vector>
#include <gtc\matrix_transform.hpp>     
#include <gtc\type_ptr.hpp> 
#include "Model.h"
#include "Pipeline.h"


//------------------------------------------------------------------------------------------------------
//function that loads raw model data from OBJ file 
//------------------------------------------------------------------------------------------------------
bool Model::LoadModel(const std::string& filename, const std::string& modelID)
{

	//variables to load and store all model data
	std::fstream file;
	std::string lineText = "";
	unsigned int tokenPosition = 0;

	std::vector<glm::vec3> faceArray;
	std::vector<glm::vec3> vertexArray;
	std::vector<glm::vec2> textureArray;
	std::vector<glm::vec3> normalArray;

	std::vector<std::string> subNumbers;
	std::vector<std::string> subStrings;

	//display text to state that file is being opened and read
	std::cout << "Opening and reading model file : " << "\"" << filename << "\"" << std::endl;

	//open model file
	file.open(filename);

	//if opening of model file failed, display error message
	if (!file)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//read in all model data until end of file is reached
	while (!file.eof())
	{

		//read line of text
		getline(file, lineText);

		//break text string into smaller substrings
		do
		{
			tokenPosition = lineText.find(' ');
			subStrings.push_back(lineText.substr(0, tokenPosition));
			lineText.erase(0, tokenPosition + 1);
		} while (tokenPosition != std::string::npos);

		//if first token is "v" or "vn", set the vertices and normal values
		if (subStrings[0] == "v" || subStrings[0] == "vn")
		{

			//if it's a vertex position, add it to the vertex array
			if (subStrings[0] == "v")
			{
				vertexArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
					(GLfloat)(atof(subStrings[2].c_str())),
					(GLfloat)(atof(subStrings[3].c_str()))));
			}

			//if it's a normal direction, add it to the normal array
			if (subStrings[0] == "vn")
			{
				normalArray.push_back(glm::vec3((GLfloat)(atof(subStrings[1].c_str())),
					(GLfloat)(atof(subStrings[2].c_str())),
					(GLfloat)(atof(subStrings[3].c_str()))));
			}

		}

		//if first token is "vt", set the UV data
		if (subStrings[0] == "vt")
		{

			//add to the textureArray
			textureArray.push_back(glm::vec2((GLfloat)(atof(subStrings[1].c_str())),
				(GLfloat)(atof(subStrings[2].c_str()))));

		}

		//if first token is "f", create a new face and set the face data
		if (subStrings[0] == "f")
		{

			//loop through all three face sub strings 
			for (int i = 1; i <= 3; i++)
			{

				//break each face substring into three face numeric values
				do
				{
					tokenPosition = subStrings[i].find('/');
					subNumbers.push_back(subStrings[i].substr(0, tokenPosition));
					subStrings[i].erase(0, tokenPosition + 1);
				} while (tokenPosition != std::string::npos);

				//add to face array
				faceArray.push_back(glm::vec3(atoi(subNumbers[0].c_str()) - 1,
					atoi(subNumbers[1].c_str()) - 1,
					atoi(subNumbers[2].c_str()) - 1));

				//clear numbers for next use
				subNumbers.clear();

			}

		}

		//clear the sub strings for next use
		subStrings.clear();

	}

	//close model file
	file.close();

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//---------------------------------
	//sift through all data for EBO
	//---------------------------------

	std::vector<GLuint> indices;
	std::vector<Groups> groups;

	//loop through all triangle faces and individually build vertex groups out of them
	//then add each vertex group to the array but first check if it's already there and
	//if it is then skip it but mark EBO to point to that existing index
	//this alleviates the problem of creating a EBO out of OBJ model file data
	for (size_t i = 0; i < faceArray.size(); i++)
	{

		//create a temporary group
		Groups tri;
		tri.vertex = vertexArray[(const unsigned int)faceArray[i].x];
		tri.texture = textureArray[(const unsigned int)faceArray[i].y];
		tri.normal = normalArray[(const unsigned int)faceArray[i].z];

		//flag for element found
		bool isFound = false;

		//set below for-loop starting point to always go 5 elements back
		//so that we don't loop through entire group array each time
		int loopStart = (groups.size() >= 5 ? groups.size() - 5 : 0);

		//loop through existing groups to see if this group already exists in there
		//and if its found use that index for the EBO otherwise continue searching
		for (size_t j = loopStart; j < groups.size(); j++)
		{

			if (tri.vertex == groups[j].vertex &&
				tri.texture == groups[j].texture &&
				tri.normal == groups[j].normal)
			{
				indices.push_back(j);
				isFound = true;
				break;
			}

		}

		//if nothing was found, it's a new group so add it and index the EBO
		if (!isFound)
		{
			groups.push_back(tri);
			indices.push_back(groups.size() - 1);
		}

	}

	//stats for vertices saved
	std::cout << "Total Vertices : " << indices.size() << std::endl;
	std::cout << "Actual Vertices : " << groups.size() << std::endl;
	std::cout << "Vertex Space Saved : "
		<< 100 - (int)((float)(groups.size()) / (float)(indices.size()) * 100) << "%" << std::endl;

	//---------------------------------
	//add all data to VBOs
	//---------------------------------

	//storage for our vertex, texture and normal data
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textures;
	std::vector<GLfloat> normals;

	//add all vertex, texture and normal data to the main vectors
	//from here this data will be fed into to VBO later on
	for (size_t j = 0; j < groups.size(); j++)
	{

		vertices.push_back(groups[j].vertex.x);
		vertices.push_back(groups[j].vertex.y);
		vertices.push_back(groups[j].vertex.z);

		textures.push_back(groups[j].texture.s);
		textures.push_back(groups[j].texture.t);

		normals.push_back(groups[j].normal.x);
		normals.push_back(groups[j].normal.y);
		normals.push_back(groups[j].normal.z);

	}

	m_buffer.CreateBuffers(modelID, indices.size(), true);

	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::TEXTURE_VBO, "textureIn", Buffer::UV, Buffer::FLOAT);
	m_buffer.BindVBO(Buffer::NORMAL_VBO, "normalIn", Buffer::NORMAL, Buffer::FLOAT);

	//filling ebo and vbo with data
	m_buffer.SetEBOData(&indices[0], indices.size() * sizeof(GLfloat), Buffer::STATIC);
	m_buffer.SetVBOData(Buffer::VERTEX_VBO, &vertices[0], vertices.size() * sizeof(GLfloat), Buffer::STATIC);
	m_buffer.SetVBOData(Buffer::TEXTURE_VBO, &textures[0], textures.size() * sizeof(GLfloat), Buffer::STATIC);
	m_buffer.SetVBOData(Buffer::NORMAL_VBO, &normals[0], normals.size() * sizeof(GLfloat), Buffer::STATIC);

	return true;

}
bool Model::LoadTexture(const std::string& filename, const std::string textureID)
{
	if (!Texture::CreateTexture2D(filename, textureID))
	{
		return false;
	}

	SetTexture(textureID);

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that unloads texture file for cube
//------------------------------------------------------------------------------------------------------
void Model::UnloadTexture(const std::string& textureID)
{

	m_texture.Unload(textureID);

}
void Model::SetTexture(const std::string textureID)
{
	m_texture.SetTexture(textureID);
	m_texture.SetMagFilter(Texture::BILINEAR);
	m_texture.SetMinFilter(Texture::TRILINEAR_MIP);
	m_texture.SetWrapMode(Texture::MIRRORED_REPEAT);
}
//------------------------------------------------------------------------------------------------------
//function that creates and fills all buffers with vertex and color data 
//------------------------------------------------------------------------------------------------------
void Model::Create()
{
	//set material color to ???
	m_material.SetShininess(1.0f);
	m_material.SetAmbient(1.0f, 1.0f, 1.0f);
	m_material.SetDiffuse(1.0f, 1.0f, 1.0f);
	m_material.SetSpecular(1.0f, 1.0f, 1.0f);
}
//------------------------------------------------------------------------------------------------------
//function that adjusts model's transformations
//------------------------------------------------------------------------------------------------------
void Model::Update(float deltaTime)
{

}
//------------------------------------------------------------------------------------------------------
//function that renders model on screen
//------------------------------------------------------------------------------------------------------
void Model::Draw()
{
	m_material.SendToShader();

	m_texture.Bind();
	
	m_buffer.Draw(Buffer::TRIANGLES);

	m_texture.UnBind();
}
//------------------------------------------------------------------------------------------------------
//function that destroys all buffer objects
//------------------------------------------------------------------------------------------------------
void Model::Destroy()
{

	//destroy EBO, VBOs and VAO
	m_buffer.DestroyBuffers();

}