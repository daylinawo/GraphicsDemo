#ifndef MODEL_H
#define MODEL_H

#include "glad.h"
#include "Buffer.h"
#include "Texture.h"
#include "Material.h"

#include <glm.hpp>
#include <string>

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class Model
{
public:

	bool LoadModel(const std::string& filename, const std::string& modelID);
	bool LoadTexture(const std::string& filename, const std::string textureID);
	void UnloadTexture(const std::string& textureID);
	void SetTexture(const std::string textureID);

public:

	void Create();
	void Update(float deltaTime);
	void Draw();
	void Destroy();

private:

	Buffer m_buffer;
	Texture m_texture;
	Material m_material;

};

#endif