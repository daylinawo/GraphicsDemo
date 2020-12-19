#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include "glad.h"
#include <map>
#include <string>
#include <vector>

enum TextureType { TEXTURE_2D, CUBE_MAP };

struct TextureID
{
	GLuint ID;
	TextureType textureType;
};

class Texture
{
public:

	enum FilterMode { NEAREST, BILINEAR, NEAREST_MIP, LINEAR_MIP, TRILINEAR_MIP, BILINEAR_MIP };
	enum WrapMode { REPEAT, MIRRORED_REPEAT, CLAMP };

public:


	static bool CreateCubeMap(const std::vector<std::string>& faces, const std::string& textureID);
	static bool CreateTexture2D(const std::string& path, const std::string& textureID);

public:

	Texture();

public:

	void SetMagFilter(FilterMode filterMode);
	void SetMinFilter(FilterMode filterMode);
	void SetWrapMode(WrapMode wrapMode);
	void SetTexture(const std::string& textureID);

public:

	void Bind();
	void UnBind();
	void Unload(const std::string& textureID);

private:

	static SDL_Surface* Load(const std::string& path, GLsizei& width, GLsizei& height, Uint8& depth);

private:

	static std::map<std::string, TextureID>* s_textureMap;

private:

	TextureID m_ID;
};


#endif 