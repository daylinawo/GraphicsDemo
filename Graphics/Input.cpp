#include "Input.h"
#include <iostream>

Input* Input::Instance()
{
	static Input* inputObject = new Input();
	return inputObject;
}

Input::Input()
{
	m_key = ' ';
	m_isXClicked = false;
	m_isKeyPressed = false;
	m_mousePositionX = 0;
	m_mousePositionY = 0;
}

bool Input::IsXClicked()
{
	return m_isXClicked;
}

char Input::GetKey()
{
	return m_key;
}

bool Input::IsKeyPressed()
{
	return m_isKeyPressed;
}

bool Input::IsKeyPressed(int keyCode)
{
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
	return keyStates[keyCode];
}

int Input::GetMousePositionX()
{
	return m_mousePositionX;
}

int Input::GetMousePositionY()
{
	return m_mousePositionY;
}

void Input::Update()
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
			case SDL_QUIT:
			{
				m_isXClicked = true;
				break;
			}		
			
			case SDL_KEYDOWN:
			{
				m_isKeyPressed = true;
				m_key = events.key.keysym.sym;
				break;
			}		
			
			case SDL_KEYUP:
			{
				m_isKeyPressed = false;
				m_key = SDLK_UNKNOWN;
				break;
			}			
			case SDL_MOUSEMOTION:
			{
				m_mousePositionX = events.motion.x;
				m_mousePositionY = events.motion.y;
				break;
			}
		}
	}
}
