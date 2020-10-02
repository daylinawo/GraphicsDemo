#pragma once
class BoxCollider
{

public:

	void SetPosition(float xPos, float yPos);
	void SetDimension(int width, int height);

public:

	bool IsColliding(const BoxCollider& secondBox) const;

private:

	void CreateBox();

private:

	float m_positionX;
	float m_positionY;

	float m_minX;
	float m_maxX;	
	float m_minY;
	float m_maxY;
	
	int m_width;
	int m_height;
};

