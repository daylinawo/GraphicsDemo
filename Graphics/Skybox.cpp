#include "Skybox.h"
#include "Input.h"
#include "Utility.h"
#include "Pipeline.h"

#include <vector>
#include <string>

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

	GLuint indices[] =
	{
		0, 1, 3, 3, 1, 2,
		4, 5, 7, 7, 5, 6,
		8, 9, 11, 11, 9, 10,
		12, 13, 15, 15, 13, 14,
		16, 17, 19, 19, 17, 18,
		20, 21, 23, 23, 21, 22
	};

	m_buffer.CreateBuffers("SKYBOX", VERTICES, true);

	//binding ebo and vbo
	m_buffer.BindEBO();
	m_buffer.BindVBO(Buffer::VERTEX_VBO, "vertexIn", Buffer::XYZ, Buffer::DataType::FLOAT);

	//filling ebo and vbo with data
	m_buffer.SetEBOData(indices, sizeof(indices), Buffer::STATIC);
	m_buffer.SetVBOData(Buffer::VERTEX_VBO, vertices, sizeof(vertices), Buffer::STATIC);

	static bool isLoaded = false;

	if (!isLoaded)
	{
		std::vector<std::string> faces
		{
			"Assets/Textures/sky_right.jpg",
			"Assets/Textures/sky_left.jpg",
			"Assets/Textures/sky_top.jpg",
			"Assets/Textures/sky_bottom.jpg",
			"Assets/Textures/sky_front.jpg",
			"Assets/Textures/sky_back.jpg"
		};

		Texture::CreateCubeMap(faces, "SKYBOX");
		isLoaded = true;
	}

	m_texture.SetTexture("SKYBOX");
	m_texture.SetMagFilter(Texture::BILINEAR);
	m_texture.SetMinFilter(Texture::LINEAR_MIP);
	m_texture.SetWrapMode(Texture::CLAMP);
}

void Skybox::Update(float deltaTime)
{

}

void Skybox::Draw()
{
	Object::SetMatrix(m_transform.GetMatrix());
	Object::SendToShader(m_isLit, m_isTextured);
	
	m_texture.Bind();

		m_buffer.Draw(Buffer::RenderMode::TRIANGLES);

	m_texture.UnBind();
}

void Skybox::Destroy()
{
	m_buffer.DestroyBuffers();
	m_texture.Unload("SKYBOX");
}