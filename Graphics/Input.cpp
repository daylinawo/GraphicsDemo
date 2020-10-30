#include "Input.h"
#include "Screen.h"
#include "Utility.h"

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

	m_mousePositionX = 0;
	m_mousePositionY = 0;
	m_mouseMotionX = 0;
	m_mouseMotionY = 0;

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

int Input::GetMousePositionX()
{
	return m_mousePositionX;
}

int Input::GetMousePositionY()
{
	return m_mousePositionY;
}

int Input::GetMouseMotionX()
{
	return m_mouseMotionX;
}

int Input::GetMouseMotionY()
{
	return m_mouseMotionY;
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
				m_mousePositionX = events.motion.x;
				m_mousePositionY = events.motion.y;

				m_mouseMotionX = events.motion.xrel;
				m_mouseMotionY = events.motion.yrel;

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				m_isMouseClicked = false;
				m_mousePositionX = events.motion.x;
				m_mousePositionY = events.motion.y;

				if (events.button.button == SDL_BUTTON_LEFT)
				{
					m_mouseButton = SDL_MOUSE_NONE;
				}

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				m_isMouseClicked = true;
				m_mousePositionX = events.motion.x;
				m_mousePositionY = events.motion.y;

				if (events.button.button == SDL_BUTTON_LEFT)
				{
					m_mouseButton = SDL_BUTTON_LEFT;
				}

				break;
			}

			case SDL_WINDOWEVENT:
			{
				if (events.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					Screen::Instance()->ResizeWindow(events.window.data1, events.window.data2);
					Utility::Log("Width: " + std::to_string(events.window.data1));
					Utility::Log("Height: " + std::to_string(events.window.data2) + "\n");
				}
				break;
			}
		}
	}
}
