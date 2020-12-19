#include "Texture.h"
#include "Utility.h"

#include <SDL_image.h>

std::map<std::string, TextureID>* Texture::s_textureMap = new std::map<std::string, TextureID>;

Texture::Texture()
{
	if (s_textureMap->empty())
	{
		CreateTexture2D("Assets/Textures/default.png", "DEFAULT");
	}

	SetTexture("DEFAULT");
}
//************************************************
//create cubemap from 6 image files
//************************************************
bool Texture::CreateCubeMap(const std::vector<std::string>& faces, const std::string& textureID)
{
	GLuint ID = 0;
	Uint8 depth = 0;
	GLint format = 0;
	GLsizei width = 0;
	GLsizei height = 0;
	Uint8* pixels = nullptr;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

		for (int i = 0; i < faces.size(); i++)
		{
			SDL_Surface* textureData = Load(faces[i], width, height, depth);

			if (!textureData)
			{
				Utility::Log("Could not create Cubemap.");
				return false;
			}

			format = ((depth == 4) ? GL_RGBA : GL_RGB);
			pixels = (Uint8*)textureData->pixels;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, 
						 width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

			SDL_FreeSurface(textureData);
		}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	s_textureMap->insert(std::pair<std::string, TextureID>(textureID, { ID, TextureType::CUBE_MAP }));

	return true;
}
//************************************************
//create 2d texture from an image file
//************************************************
bool Texture::CreateTexture2D(const std::string& path, const std::string& textureID)
{
	GLuint ID = 0;
	Uint8 depth = 0;
	GLint format = 0;
	GLsizei width = 0;
	GLsizei height = 0;
	Uint8* pixels = nullptr;

	if (s_textureMap->find(textureID) != s_textureMap->end())
	{
		Utility::Log("This texture ID already exists: " + textureID);
		return false;
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

		SDL_Surface* textureData = Load(path, width, height, depth);

		if (!textureData)
		{
			Utility::Log("Could not create Texture 2D.");
			return false;
		}

		format = ((depth == 4) ? GL_RGBA : GL_RGB);
		pixels = (Uint8*)textureData->pixels;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		SDL_FreeSurface(textureData);

	glBindTexture(GL_TEXTURE_2D, 0);

	s_textureMap->insert(std::pair<std::string, TextureID>(textureID, { ID, TextureType::TEXTURE_2D }));

	return true;
}
//************************************************
//load texture image from file
//************************************************
SDL_Surface* Texture::Load(const std::string& path, GLsizei& width, GLsizei& height, Uint8& depth)
{
	SDL_Surface* textureData = nullptr;
	textureData = IMG_Load(path.c_str());

	if (!textureData)
	{
		Utility::Log("Could not load texture file: \"" + path + " \"");
	}

	width = textureData->w;
	height = textureData->h;
	depth = textureData->format->BytesPerPixel;

	return textureData;
}

//************************************************
//set texture
//************************************************
void Texture::SetTexture(const std::string& textureID)
{
	auto it = s_textureMap->find(textureID);

	if (it != s_textureMap->end())
	{
		m_ID = it->second;
	}
	else
	{
		Utility::Log("Could not assign texture ID: " + textureID);
	}
}
//************************************************
//bind texture
//************************************************
void Texture::Bind()
{
	GLenum target = (m_ID.textureType == TextureType::CUBE_MAP) ? 
					 GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

	glBindTexture(target, m_ID.ID);
}
//************************************************
//unbind texture
//************************************************
void Texture::UnBind()
{
	GLenum target = (m_ID.textureType == TextureType::CUBE_MAP) ?
					 GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

	glBindTexture(target, 0);
}
//************************************************
//set texture wrapping
//************************************************
void Texture::SetWrapMode(WrapMode wrapMode)
{
	GLenum target = (m_ID.textureType == TextureType::CUBE_MAP) ?
					 GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

	Bind();

		switch (wrapMode)
		{
			case WrapMode::REPEAT:
			{
				glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;
			}
			case WrapMode::MIRRORED_REPEAT:
			{
				glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				break;
			}
			case WrapMode::CLAMP:
			{
				glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;
			}
		}

	UnBind();
}
//************************************************
//set magnification filter
//************************************************
void Texture::SetMagFilter(FilterMode filterMode)
{
	GLenum target = (m_ID.textureType == TextureType::CUBE_MAP) ?
					 GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

	Bind();

		switch (filterMode)
		{
			case FilterMode::NEAREST: { glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST); break; }
			case FilterMode::BILINEAR: { glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR); break; }
		}

	UnBind();
}
//************************************************
//set minification filter
//************************************************
void Texture::SetMinFilter(FilterMode filterMode)
{
	GLenum target = (m_ID.textureType == TextureType::CUBE_MAP) ?
					 GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

	Bind();

		switch (filterMode)
		{
			case FilterMode::NEAREST:
			{
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			}
			case FilterMode::BILINEAR:
			{
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}
			case FilterMode::NEAREST_MIP:
			{
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				glGenerateMipmap(target);
				break;
			}
			case FilterMode::LINEAR_MIP:
			{
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				glGenerateMipmap(target);
				break;
			}
			case FilterMode::TRILINEAR_MIP:
			{
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glGenerateMipmap(target);
				break;
			}
			case FilterMode::BILINEAR_MIP:
			{
				glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				glGenerateMipmap(target);
				break;
			}
		}

	UnBind();
}
//************************************************
//delete textures from memory
//************************************************
void Texture::Unload(const std::string& textureID)
{
	auto it = s_textureMap->find(textureID);

	if (it == s_textureMap->end())
	{
		Utility::Log("Could not find texture: " + textureID);
	}
	else
	{
		glDeleteTextures(1, &(it->second.ID));
		s_textureMap->erase(it);

		Utility::Log("Successfully unloaded texture: " + textureID);
	}
}
