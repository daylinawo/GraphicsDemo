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
	m_isKeyPressed = false;
	m_isMouseClicked = false;
	m_isWindowClosed = false;

	m_mousePosition = { 0, 0 };
	m_mouseMotion = { 0, 0 };

	m_mouseButton = SDL_MOUSE_NONE;
}

bool Input::IsWindowClosed()
{
	return m_isWindowClosed;
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

bool Input::IsMouseClicked(int mouseButton)
{
	return m_mouseButton == mouseButton;
}

const Vector<int>& Input::GetMousePosition() const
{
	return m_mousePosition;
}

const Vector<int>& Input::GetMouseMotion() const
{
	return m_mouseMotion;
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
				m_isWindowClosed = true;
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
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;

				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.y = events.motion.yrel;

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				m_isMouseClicked = false;
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;

				if (events.button.button == SDL_BUTTON_LEFT)
				{
					m_mouseButton = SDL_MOUSE_NONE;
				}

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				m_isMouseClicked = true;
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;

				if (events.button.button == SDL_BUTTON_LEFT)
				{
					m_mouseButton = SDL_BUTTON_LEFT;
				}

				break;
			}

		}
	}
}
