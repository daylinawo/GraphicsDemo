#pragma once

#define SDL_MOUSE_NONE 0


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
	int GetMousePositionX();
	int GetMousePositionY();
	int GetMouseMotionX();
	int GetMouseMotionY();

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

private:

	char m_key;

	bool m_isKeyPressed;
	bool m_isWindowClosed;
	bool m_isMouseClicked;

	int m_mousePositionX;
	int m_mousePositionY;
	int m_mouseMotionX;
	int m_mouseMotionY;

	int m_mouseButton;

};

