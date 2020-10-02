#pragma once

#include <SDL.h>

class Input
{

public:

	static Input* Instance();


public:

	void Update();

public:

	bool IsWindowClosed();
	char GetKey();
	bool IsKeyPressed();
	bool IsKeyPressed(int keyCode);
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

	int m_mousePositionX;
	int m_mousePositionY;	
	int m_mouseMotionX;
	int m_mouseMotionY;
};

