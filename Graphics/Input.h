#pragma once

#define SDL_MOUSE_NONE 0


#include <SDL.h>
#include "Vector.h"

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
	const Vector<int>& GetMousePosition() const;
	const Vector<int>& GetMouseMotion() const;

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

private:

	char m_key;

	bool m_isKeyPressed;
	bool m_isWindowClosed;
	bool m_isMouseClicked;

	Vector<int> m_mousePosition;
	Vector<int> m_mouseMotion;

	int m_mouseButton;

};

