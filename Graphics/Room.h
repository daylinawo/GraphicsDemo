#ifndef ROOM_H
#define ROOM_H

#include "Object.h"
#include "Plane.h"
#include <vector>

class Room : public Object
{
public:
	
	Room();
	~Room() {};

public:

	void Create(float width, float height, float depth);
	void Update(float deltaTime);
	void Draw();
	void Destroy();

private:

	float m_width;
	float m_height;
	float m_depth;

	Plane* m_floor;
	std::vector<Plane*> m_walls;

};

#endif


