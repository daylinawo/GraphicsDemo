#pragma once

#include <SDL.h>

class Input
{

public:

	static Input* Instance();


public:

	void Update();

public:

	bool IsXClicked();
	char GetKey();
	bool IsKeyPressed();
	bool IsKeyPressed(int keyCode);
	int GetMousePositionX();
	int GetMousePositionY();

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

private:

	bool m_isXClicked;
	bool m_isKeyPressed;
	char m_key;
	int m_mousePositionX;
	int m_mousePositionY;
};

