#ifndef GRID_H
#define GRID_H

#include "Buffer.h"
#include <gtc\matrix_transform.hpp>

class Grid
{

public:

	Grid();
	~Grid();

public:

	void CreateGrid();
	void CreateAxes();

public:

	void DrawGrid();
	void DrawAxes();

private:

	Buffer m_gridBuffer;
	Buffer m_axesBuffer;

	glm::vec3 m_colors;
	glm::vec3 m_position;
	glm::mat4 m_model;

};

#endif


