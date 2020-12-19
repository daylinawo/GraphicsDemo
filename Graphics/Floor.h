#ifndef FLOOR_H
#define FLOOR_H

#include "Object.h"

class Floor : public Object
{

public:

	Floor();
	~Floor() {};

public:

	void Create();
	void Destroy();

public:

	void Update(float deltaTime);
	void Draw();


};

#endif

