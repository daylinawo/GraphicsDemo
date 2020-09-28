#include "Screen.h"
#include "Utility.h"

#include <iostream>
#include <vector>
#include <map>

Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}

Screen::Screen()
{
	m_window = nullptr;
	m_context = nullptr;
}

bool Screen::Initialize(const std::string& windowName, int width, int height,
						bool fullscreen, bool coreMode, bool openGLScreen)
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


	//set a compatibility OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, coreMode);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


	if (!SetupWindow(windowName, width, height, fullscreen, openGLScreen))
	{
		return false;
	}

	gladLoadGL();
	return true;
}


bool Screen::SetupWindow(const std::string& windowTitle, int width, 
						 int height, bool fullscreen, bool openGLScreen)
{

	Uint32 screenFlag = (std::stoi(m_settings["FullScreen"])) ? SDL_WINDOW_FULLSCREEN : 0;
	screenFlag |= (std::stoi(m_settings["OpenGLScreen"])) ? SDL_WINDOW_OPENGL : 0;

	m_window = SDL_CreateWindow(windowTitle,
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

void Screen::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}
