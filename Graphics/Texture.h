#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad.h"

#include <string>
#include <map>

class Texture
{
public:

	enum class FilterMode { NEAREST, BILINEAR, NEAREST_MIP, LINEAR_MIP, TRILINEAR_MIP, BILINEAR_MIP };
	enum class TextureType { _2D, CUBEMAP };
	enum class WrapMode { REPEAT, MIRRORED_REPEAT, CLAMP };

public:

	static bool GetTexture(const std::string& textureID, Texture& texture);

public:

	Texture();

public:

	void SetMagFilter(FilterMode filterMode);
	void SetMinFilter(FilterMode filterMode);
	void SetWrapMode(WrapMode wrapMode);

	void SetTexture(const std::string& textureID);

public:

	void Bind();
	void Load(const std::string& path, const std::string& textureID);
	void UnBind();
	void Unload();

private:

	static std::map<std::string, Texture>* s_textureMap;

private:

	GLuint m_ID;
};


#endif 