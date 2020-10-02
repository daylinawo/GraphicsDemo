#include "BoxCollider.h"

void BoxCollider::SetPosition(float xPos, float yPos)
{
	m_positionX = xPos;
	m_positionY = yPos;

	CreateBox();
}

void BoxCollider::SetDimension(int width, int height)
{
	m_width = width;
	m_height = height;

	CreateBox();

}

bool BoxCollider::IsColliding(const BoxCollider& secondBox) const
{
	return ((m_maxX > secondBox.m_minX && secondBox.m_maxX > m_minX) &&
			(m_maxY > secondBox.m_minY && secondBox.m_maxY > m_minY));
}

void BoxCollider::CreateBox()
{
	m_minX = m_positionX - m_width / 2;;
	m_maxX = m_positionX + m_width / 2;;
	m_minY = m_positionY - m_height / 2;;
	m_maxY = m_positionY + m_height / 2;
}
