#pragma once

#define SDL_MOUSE_NONE 0

#include <glm.hpp>
#include <SDL.h>

class Input
{

public:

	static Input* Instance();

public:

	void Update();

public:

	bool IsWindowClosed();
	
	bool IsKeyPressed();
	bool IsKeyPressed(int keyCode);
	bool IsMouseClicked(int mouseButton);

	char GetKey();

	const glm::vec2& GetMousePosition();
	const glm::vec2& GetMouseMotion();
	const glm::vec2& GetMouseWheel();

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

private:

	char m_key;
	int m_mouseButton;

	bool m_isKeyPressed;
	bool m_isWindowClosed;
	bool m_isMouseClicked;

	glm::vec2 m_mousePosition;
	glm::vec2 m_mouseMotion;
	glm::vec2 m_mouseWheel;
};

