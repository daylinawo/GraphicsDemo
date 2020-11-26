#include "Skybox.h"
#include "Input.h"
#include "Utility.h"

const int VERTICES = 36;

Skybox::Skybox()
{
	m_tag = "Skybox";
	m_isLit = false;
	m_isTextured = true;
}

void Skybox::Create()
{
	GLfloat vertices[] =
	{
		//front face
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		//back face
		-1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		//left face
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,

		//right face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,

		//top face
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, 1.0f,

		 //bottom face
		 -1.0f, -1.0f, 1.0f,
		 -1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f, 1.0f,
	};

	GLfloat colors[] =
	{
		// front face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		//back face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		//left face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		//right face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		//top face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		//bottom face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};

	GLfloat UV[] =
	{
		//front face
		1.0f, 0.33f, 0.75f, 0.33f,
		0.75f, 0.66f, 1.0f, 0.66f,

		//back face
		0.25f, 0.33f, 0.5f, 0.33f,
		0.5f, 0.66f, 0.25f, 0.66f,

		//left face
		0.0f, 0.33f, 0.25f, 0.33f,
		0.25f, 0.66f, 0.0f, 0.66f,

		//right face
		0.75f, 0.33f, 0.5f, 0.33f,
		0.5f, 0.66f, 0.75f, 0.66f,

		//top face
		0.25f, 0.0f, 0.25f, 0.33f,
		0.5f, 0.33f, 0.5f, 0.0f,

		//bottom face
		 0.25f, 1.0f, 0.25f, 0.66f,
		 0.5f, 0.66f, 0.5f, 1.0f,

	};

	GLfloat normals[] =
	{
		//front face
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		//back face
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,

		//left face
		-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		//right face
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		//top face
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		//bottom face
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f
	};

	GLuint indices[] =
	{
		0, 1, 3, 3, 1, 2,
		4, 5, 7, 7, 5, 6,
		8, 9, 11, 11, 9, 10,
		12, 13, 15, 15, 13, 14,
		16, 17, 19, 19, 17, 18,
		20, 21, 23, 23, 21, 22
	};

	m_buffer.CreateBuffers(VERTICES, true);

	//binding ebo and vbo
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VBOType::VERTEX, "vertexIn", Buffer::ComponentType::XYZ, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::COLOR, "colorIn", Buffer::ComponentType::RGB, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::TEXTURE, "textureIn", Buffer::ComponentType::UV, Buffer::DataType::FLOAT);
	m_buffer.BindVBO(Buffer::VBOType::NORMAL, "normalIn", Buffer::ComponentType::NORMAL, Buffer::DataType::FLOAT);

	//filling ebo and vbo with data
	m_buffer.SetEBOData(indices, sizeof(indices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::VERTEX, vertices, sizeof(vertices), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::COLOR, colors, sizeof(colors), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::TEXTURE, UV, sizeof(UV), Buffer::DataMode::STATIC);
	m_buffer.SetVBOData(Buffer::VBOType::NORMAL, normals, sizeof(normals), Buffer::DataMode::STATIC);

	static bool isLoaded = false;

	if (!isLoaded)
	{
		m_texture.Load("Assets/Textures/skybox.png", "SKYBOX");
		m_texture.SetMagFilter(Texture::FilterMode::BILINEAR);
		m_texture.SetMinFilter(Texture::FilterMode::TRILINEAR_MIP);
		m_texture.SetWrapMode(Texture::WrapMode::MIRRORED_REPEAT);

		isLoaded = true;
	}

}

void Skybox::Destroy()
{
}

void Skybox::Update(float deltaTime)
{

}

void Skybox::Draw()
{
	SendToShader();

	m_texture.Bind();

	m_buffer.Draw(Buffer::RenderMode::TRIANGLES);

	m_texture.UnBind();
}

Skybox::~Skybox()
{
}
