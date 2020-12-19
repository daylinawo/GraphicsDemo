#include "Room.h"

Room::Room()
{
	m_width = 0.0f;
	m_height = 0.0f;
	m_depth = 0.0f;

	m_floor = nullptr;
}

void Room::Create(float width, float height, float depth)
{
	//floor
	m_floor = new Plane("Assets/Textures/Wood_2.jpg", "WOOD_2");
	m_floor->Create();
	m_floor->GetTransform().Scale(width, depth, 0.0f);
	m_floor->GetTransform().Rotate(90.0f, 0.0f, 0.0f);

	//Far Wall
	m_walls.push_back(new Plane("Assets/Textures/Wallpaper_1.jpg", "WALLPAPER_1"));
	m_walls.back()->Create();
	m_walls.back()->GetTransform().Scale(width, height, 0.0f);
	m_walls.back()->GetTransform().Translate(0.0f, height + 1, -(depth + 1));

	//Right Wall
	m_walls.push_back(new Plane());
	m_walls.back()->Create();
	m_walls.back()->GetTransform().Scale(depth, height, 0.0f);
	m_walls.back()->GetTransform().Rotate(0.0f, 90.0f, 0.0f);
	m_walls.back()->GetTransform().Translate(width + 1, height + 1, 0.0f);
	m_walls.back()->SetTexture("WALLPAPER_1");

	//Back Wall
	m_walls.push_back(new Plane());
	m_walls.back()->Create();
	m_walls.back()->GetTransform().Scale(width, height, 0.0f);
	m_walls.back()->GetTransform().Translate(0.0f, height + 1, depth + 1);
	m_walls.back()->SetTexture("WALLPAPER_1");

	//Left Wall
	m_walls.push_back(new Plane());
	m_walls.back()->Create();
	m_walls.back()->GetTransform().Scale(depth, height, 0.0f);
	m_walls.back()->GetTransform().Rotate(0.0f, 90.0f, 0.0f);
	m_walls.back()->GetTransform().Translate(-(width + 1), height + 1, 0.0f);
	m_walls.back()->SetTexture("WALLPAPER_1");

}

void Room::Update(float deltaTime)
{
	m_floor->Update(deltaTime);
}

void Room::Draw()
{
	m_floor->Draw();

	for (auto it = m_walls.begin(); it != m_walls.end(); it++)
	{
		(*it)->Draw();
	}
}

void Room::Destroy()
{
	m_floor->Destroy();

	delete m_floor;

	for (auto it = m_walls.begin(); it != m_walls.end(); it++)
	{
		(*it)->Destroy();
		delete (*it);
	}
	
	m_walls.clear();
}
