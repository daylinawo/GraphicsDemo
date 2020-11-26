#include "Texture.h"
#include "Utility.h"

#include <SDL.h>
#include <SDL_image.h>

std::map<std::string, Texture>* Texture::s_textureMap = new std::map<std::string, Texture>;

Texture::Texture()
{
	glGenTextures(1, &m_ID);
}

void Texture::SetMagFilter(FilterMode filterMode)
{
	Bind();

	switch (filterMode)
	{
		case FilterMode::NEAREST:  { glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); break; }		
		case FilterMode::BILINEAR: { glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); break;  }
	}

	UnBind();
}

void Texture::SetMinFilter(FilterMode filterMode)
{
	Bind();

	switch (filterMode)
	{
		case FilterMode::NEAREST: 
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
			break; 
		}
		case FilterMode::BILINEAR: 
		{ 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
			break;  
		}	
		case FilterMode::NEAREST_MIP:
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
		}
		case FilterMode::LINEAR_MIP: 
		{ 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;  
		}
		case FilterMode::TRILINEAR_MIP: 
		{ 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
			glGenerateMipmap(GL_TEXTURE_2D);
			break;  
		}	
		case FilterMode::BILINEAR_MIP: 
		{ 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;  
		}	
	}

	UnBind();
}

void Texture::SetWrapMode(WrapMode wrapMode)
{
	Bind();

	switch (wrapMode)
	{
		case WrapMode::REPEAT:
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		}		
		case WrapMode::MIRRORED_REPEAT:
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			break;
		}	
		case WrapMode::CLAMP:
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		}
	}

	UnBind();
}

void Texture::SetTexture(const std::string& textureID)
{
	auto it = s_textureMap->find(textureID);

	if (it != s_textureMap->end())
	{
		m_ID = it->second.m_ID;
	}
	else
	{
		Utility::Log("Could not set texture ID: " + textureID);
	}
}

bool Texture::GetTexture(const std::string& textureID, Texture& texture)
{
	auto it = s_textureMap->find(textureID);

	if (it != s_textureMap->end())
	{
		texture = it->second;
		return true;
	}
	else
	{
		Utility::Log("Could not find texture ID: " + textureID);
	}

	return false;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Load(const std::string& path, const std::string& textureID)
{
	SDL_Surface* textureData = nullptr;
	textureData = IMG_Load(path.c_str());

	if (!textureData)
	{
		Utility::Log("Could not load texture file: \"" + path + " \"");
		return;
	}

	GLsizei width = textureData->w;
	GLsizei height = textureData->h;
	Uint8* pixels = (Uint8*)textureData->pixels;
	Uint8 depth = textureData->format->BytesPerPixel;
	GLint format = ((depth == 4) ? GL_RGBA : GL_RGB);

	Bind();

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	UnBind();

	SDL_FreeSurface(textureData);

	s_textureMap->insert(std::pair<std::string, Texture>(textureID, *this));
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Unload()
{
	glDeleteTextures(1, &m_ID);
}
