#include "Quad.h"
#include "Input.h"
#include "Pipeline.h"
#include "Screen.h"
#include "Utility.h"

const int VERTICES = 6;

Quad::Quad()
{
	m_tag = "Quad";
	m_isLit = false;
	m_isTextured = true;
}

void Quad::Create(GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b)
{
	GLfloat vertices[] =
	{
		-width, height, 0.0f,
		 width, height, 0.0f,
		 width, -height, 0.0f,
		-width, -height, 0.0f
	};

	GLfloat colors[] =
	{
		r, g, b,
		r, g, b,
		r, g, b,
		r, g, b
	};

	GLfloat UV[] =
	{
		0.0f, 0.0f,
		3.0f, 0.0f,
		3.0f, 3.0f,
		0.0f, 3.0f
	};
		
	GLfloat normals[] =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint indices[] = { 0, 1, 3, 3, 1, 2 };

	m_buffer.CreateBuffers(VERTICES, true);

	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VBOType::VERTEX, "vertexIn", Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::COLOR, "colorIn", Buffer::ComponentType::RGB, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::TEXTURE, "textureIn", Buffer::ComponentType::UV, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::NORMAL, "normalIn", Buffer::ComponentType::NORMAL, Buffer::DataType::FLOAT);

	m_buffer.SetEBOData(indices, sizeof(indices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::VERTEX, vertices, sizeof(vertices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::COLOR, colors, sizeof(colors), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::TEXTURE, UV, sizeof(UV), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::NORMAL, normals, sizeof(normals), Buffer::DataMode::STATIC);

	static bool isLoaded = false;

	if (!isLoaded)
	{
		m_texture.Load("Assets/Textures/metal.png", "METAL");

		m_texture.SetMagFilter(Texture::FilterMode::BILINEAR);
		m_texture.SetMinFilter(Texture::FilterMode::TRILINEAR_MIP);
		m_texture.SetWrapMode(Texture::WrapMode::MIRRORED_REPEAT);

		isLoaded = true;
	}

}

void Quad::Update(float deltaTime)
{
	static bool isKeyPressed = false;

	//toggle outline mode on/off
	if (Input::Instance()->IsKeyPressed(SDL_SCANCODE_L) && !isKeyPressed)
	{
		m_isLit = !m_isLit;

		(m_isLit) ? Utility::Log(m_tag + " is lit") :
					Utility::Log(m_tag + " is unlit");
	}

	//track key press so that action is only performed once on key down
	isKeyPressed = Input::Instance()->IsKeyPressed(SDL_SCANCODE_L);
}

void Quad::Draw()
{
	SendToShader();

	m_texture.Bind();

		m_buffer.Draw(Buffer::RenderMode::TRIANGLES);
		
	m_texture.UnBind();
}

void Quad::Destroy()
{
	m_buffer.DestroyBuffers();
}
