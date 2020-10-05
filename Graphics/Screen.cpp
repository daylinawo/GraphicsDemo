#include "Screen.h"
#include "Utility.h"

#include <iostream>


Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}

Screen::Screen()
{
	m_window = nullptr;
	m_context = nullptr;
	m_width = NULL;
	m_height = NULL;
}

void Screen::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}

void Screen::DisplayProfile()
{
	std::cout << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
}

void Screen::DisplayExtensions()
{
	GLint totalExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	for (GLint i = 0; i < totalExtensions; i++)
	{
		std::cout << "Extension #" << i << " : "
				  << reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)) << std::endl;
	}
}

int Screen::GetWidth()
{
	return m_width;
}

int Screen::GetHeight()
{
	return m_height;
}

bool Screen::Initialize(const std::string& windowName, int width, int height,
						bool fullscreen, bool coreMode, bool openGLScreen)
{	

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		std::cout << "Could not initialize SDL." << std::endl;
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

	int mode = (coreMode) ? static_cast<int>(SDL_GL_CONTEXT_PROFILE_CORE) :
							static_cast<int>(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	//set a compatibility OpenGL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, mode);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	if (!SetupWindow(windowName, width, height, fullscreen, openGLScreen))
	{
		return false;
	}

	if (!gladLoadGL())
	{
		std::cout << "Could not load glad." << std::endl;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);

	return true;
}


bool Screen::SetupWindow(const std::string& windowTitle, int width, 
						 int height, bool fullscreen, bool openGLScreen)
{
	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;
	screenFlag |= (openGLScreen) ? SDL_WINDOW_OPENGL : 0;

	m_window = SDL_CreateWindow(windowTitle.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width, height, 
								screenFlag);

	if (!m_window)
	{
		std::cout << "Window could not be created." << std::endl;
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);

	if (!m_context)
	{
		std::cout << "OpenGL context could not be created." << std::endl;
		return false;
	}

	m_width = width;
	m_height = height;

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
