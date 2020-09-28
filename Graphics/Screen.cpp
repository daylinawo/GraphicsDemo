#include "Screen.h"
#include <iostream>
#include "Utility.h"
#include <vector>
#include <map>

Screen::Screen()
{
	m_window = nullptr;
	m_context = nullptr;
	m_isRunning = false;

	std::vector<std::string> settings;
	std::vector<std::string> strBuffer;

	Utility::GetFileContents("Assets/Files/settings.ini", settings);

	if (!settings.empty())
	{
		for (auto it = settings.begin(); it != settings.end(); it++)
		{
			strBuffer.clear();
			Utility::ParseString((*it), '=', strBuffer);

			m_settings.insert({ strBuffer[0], strBuffer[1] });
		}
	}
}

bool Screen::Initialize()
{	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		std::cout << "Could not initialize SDL" << std::endl;
		return false;
	}

	//Set RGBA buffer sizes and total buffer size
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	int mode = (std::stoi(m_settings["CoreMode"])) ? (int)SDL_GL_CONTEXT_PROFILE_CORE : (int)SDL_GL_CONTEXT_PROFILE_COMPATIBILITY;

	//set a compatibility OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, mode);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


	if (!SetupWindow())
	{
		return false;
	}

	return true;
}


bool Screen::SetupWindow()
{

	Uint32 screenFlag = (std::stoi(m_settings["FullScreen"])) ? SDL_WINDOW_FULLSCREEN : 0;
	screenFlag |= (std::stoi(m_settings["OpenGLScreen"])) ? SDL_WINDOW_OPENGL : 0;

	m_window = SDL_CreateWindow(m_settings["WindowTitle"].c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								std::stoi(m_settings["ScreenWidth"]), 
								std::stoi(m_settings["ScreenHeight"]), 
								screenFlag);

	if (!m_window)
	{
		std::cout << "Scene window could not be created." << std::endl;
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);

	if (!m_context)
	{
		std::cout << "OpenGL context could not be created" << std::endl;
		return false;
	}

	m_isRunning = true;

	return true;
}

void Screen::Shutdown()
{
	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();
}

bool Screen::IsRunning()
{
	return m_isRunning;
}

SDL_Window* Screen::GetWindow()
{
	return m_window;
}

Screen::~Screen()
{
}