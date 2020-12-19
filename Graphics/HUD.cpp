#include "HUD.h"
#include "Screen.h"
#include "Primitives.h"

HUD::HUD()
{
	m_texture.CreateTexture2D("Assets/Sprites/light_controls_hud.png", "LIGHTING_CONTROLS");
	m_texture.SetTexture("LIGHTING_CONTROLS");
}

void HUD::Create()
{
	m_texture.SetMagFilter(Texture::BILINEAR);
	m_texture.SetMinFilter(Texture::TRILINEAR_MIP);
	m_texture.SetWrapMode(Texture::MIRRORED_REPEAT);
}

void HUD::Update(float deltaTime)
{
}

void HUD::Draw()
{
	Screen::Instance()->SetScreen2D();

	Object::SetIdentity();
	Object::Scale(400.0f, 226.0f, 0.0f);

	m_texture.Bind();
	
	Primitives::Instance()->DrawQuad2D(false, true);
	
	m_texture.UnBind();
}

void HUD::Destroy()
{
	m_texture.Unload("LIGHTING_CONTROLS");
}
