#include "Plane.h"
#include "Primitives.h"

Plane::Plane(const std::string& filename, const std::string& textureID)
{
	m_tag = "Plane";
	m_isLit = true;

	if (filename != "none")
	{
		Texture::CreateTexture2D(filename, textureID);
		m_texture.SetTexture(textureID);
		m_textureID = textureID;
		m_isTextured = true;
	}
}

void Plane::Create()
{
	m_material.SetAmbient(1.0f, 1.0f, 1.0f);
	m_material.SetDiffuse(1.0f, 1.0f, 1.0f);
	m_material.SetSpecular(1.0f, 1.0f, 1.0f);
	m_material.SetShininess(0.4f);

	m_texture.SetMagFilter(Texture::FilterMode::BILINEAR);
	m_texture.SetMinFilter(Texture::FilterMode::TRILINEAR_MIP);
	m_texture.SetWrapMode(Texture::WrapMode::MIRRORED_REPEAT);
}

void Plane::Update(float deltaTime)
{
}

void Plane::Draw()
{
	m_material.SendToShader();

	SetMatrix(m_transform.GetMatrix());

	m_texture.Bind();

		Primitives::Instance()->DrawQuad3D(m_isLit, m_isTextured);

	m_texture.UnBind();
}

void Plane::SetTexture(const std::string& textureID)
{
	m_texture.SetTexture(textureID);
	m_isTextured = true;
}

Material& Plane::GetMaterial()
{
	return m_material;
}

void Plane::Destroy()
{
	if (!m_textureID.empty())
	{
		m_texture.Unload(m_textureID);
	}
}