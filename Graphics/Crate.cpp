#include "Crate.h"
#include "Primitives.h"

Crate::Crate()
{
	m_tag = "Crate";
	m_isLit = true;
	m_isTextured = true;

	static bool isLoaded = false;

	if (!isLoaded)
	{
		Texture::CreateTexture2D("Assets/Textures/crate.jpg", "CRATE");
		isLoaded = true;
	}
}

void Crate::Create()
{
	m_texture.SetTexture("CRATE");
	m_texture.SetMagFilter(Texture::FilterMode::BILINEAR);
	m_texture.SetMinFilter(Texture::FilterMode::TRILINEAR_MIP);
	m_texture.SetWrapMode(Texture::WrapMode::MIRRORED_REPEAT);

	m_material.SetAmbient(0.24725f, 0.1995f, 0.0745f);
	m_material.SetDiffuse(0.75164f, 0.60648f, 0.22648f);
	m_material.SetSpecular(0.628281f, 0.555802f, 0.366065f);
	m_material.SetShininess(0.4f);
}


void Crate::Update(float deltaTime)
{
	//
}

void Crate::Draw()
{
	m_material.SendToShader();

	m_texture.Bind();

	SetMatrix(m_transform.GetMatrix());

	Primitives::Instance()->DrawCube3D(m_isLit, m_isTextured);

	m_texture.UnBind();
}

void Crate::Destroy()
{
	m_texture.Unload("CRATE");
}