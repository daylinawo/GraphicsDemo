#include "Cube.h"
#include "Pipeline.h"
#include "Screen.h"
#include "Input.h"
#include "Utility.h"

const int VERTICES = 36;

Cube::Cube()
{
	m_tag = "Cube";
	m_isLit = false;
	m_isTextured = true;
}

void Cube::Create(GLfloat width, GLfloat height, GLfloat depth, const glm::vec3& color)
{
	GLfloat vertices[] =
	{
		//front face
		-width, height, depth,
		 width, height, depth,
		 width, -height, depth,
		-width, -height, depth,

		//back face
		-width, height, -depth,
		 width, height, -depth,
		 width, -height, -depth,
		-width, -height, -depth,

		//left face
		-width, height, depth,
		-width, height, -depth,
		-width, -height, -depth,
		-width, -height, depth,

		//right face
		width, height, depth,
		width, height, -depth,
		width, -height, -depth,
		width, -height, depth,

		//top face
		-width, height, depth,
		-width, height, -depth,
		 width, height, -depth,
		 width, height, depth,

		//bottom face
		-width, -height, depth,
		-width, -height, -depth,
		 width, -height, -depth,
		 width, -height, depth,
	};

	GLfloat colors[] =
	{
		// front face
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,

		//back face
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,

		//left face
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,

		//right face
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,

		//top face
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,

		//bottom face
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
	};

	GLfloat UV[] =
	{
		//front face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//back face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//left face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//right face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//top face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		//bottom face
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f
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

	m_texture.Load("Assets/Textures/crate.jpg", "CRATE");
	m_texture.SetMagFilter(Texture::FilterMode::BILINEAR);
	m_texture.SetMinFilter(Texture::FilterMode::TRILINEAR_MIP);
	m_texture.SetWrapMode(Texture::WrapMode::MIRRORED_REPEAT);
}

void Cube::Update(float deltaTime)
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

void Cube::Draw()
{
	SendToShader();

	m_texture.Bind();

		m_buffer.Draw(Buffer::RenderMode::TRIANGLES);
	
	m_texture.UnBind();
}

void Cube::Destroy()
{
	m_buffer.DestroyBuffers();
	m_texture.Unload();
}

Cube::~Cube()
{
	Destroy();
}