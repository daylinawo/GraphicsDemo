#pragma once
class Quad
{

public:

	struct Colour 
	{
		float r;
		float g;
		float b;
	};

public:

	Quad(float xPos, float yPos, int width, int height, 
		 float r = 0.0f, float g = 0.0f, float b = 0.0f);
	~Quad();

public:

	void Update();
	void Draw();

public:

	void SetPosition(float x, float y);
	
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();

private:
	
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	Colour m_colour;

};

