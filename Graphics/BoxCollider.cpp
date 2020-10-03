#include "BoxCollider.h"

void BoxCollider::SetPosition(float xPos, float yPos)
{
	m_position = { xPos, yPos };
	CreateBox();
}

void BoxCollider::SetDimension(int width, int height)
{
	m_dimension.x = width;
	m_dimension.y = height;

	CreateBox();
}

bool BoxCollider::IsColliding(const BoxCollider& secondBox) const
{
	return ((m_max.x > secondBox.m_min.x && secondBox.m_max.x> m_min.x) &&
			(m_max.y > secondBox.m_min.y && secondBox.m_max.y > m_min.y));
}

void BoxCollider::CreateBox()
{
	m_min.x = m_position.x - m_dimension.x / 2;
	m_max.x = m_position.x + m_dimension.x / 2;
	m_min.y = m_position.y - m_dimension.y / 2;
	m_max.y = m_position.y + m_dimension.y / 2;
}
