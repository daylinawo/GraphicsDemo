#include "MetalBox.h"
#include "Primitives.h"

MetalBox::MetalBox()
{
	m_tag = "MetalBox";
	m_isLit = true;
	m_isTextured = true;

	static bool isLoaded = false;

	if (!isLoaded)
	{
		Texture::CreateTexture2D("Assets/Textures/metalbox.jpg", "METALBOX");
		isLoaded = true;
	}
}

void MetalBox::Create()
{
	m_texture.SetTexture("METALBOX");
	m_texture.SetMagFilter(Texture::FilterMode::BILINEAR);
	m_texture.SetMinFilter(Texture::FilterMode::TRILINEAR_MIP);
	m_texture.SetWrapMode(Texture::WrapMode::MIRRORED_REPEAT);

	m_material.SetAmbient(0.25f, 0.25f, 0.25f);
	m_material.SetDiffuse(0.4f, 0.4f, 0.4f);
	m_material.SetSpecular(0.774597f, 0.774597f, 0.774597f);
	m_material.SetShininess(0.6f);
}

void MetalBox::Update(float deltaTime)
{
	//
}

void MetalBox::Draw()
{
	m_material.SendToShader();

	m_texture.Bind();

	SetMatrix(m_transform.GetMatrix());

	Primitives::Instance()->DrawCube3D(m_isLit, m_isTextured);

	m_texture.UnBind();
}


void MetalBox::Destroy()
{
	m_texture.Unload("METALBOX");
}