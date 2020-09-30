#pragma once

#include "glad.h"
#include <SDL.h>
#include <string>
#include <map>

class Screen
{
public:

	static Screen* Instance();

public:

	void Shutdown();
	bool Initialize(const std::string& windowTitle, int width, int height,
					bool fullscreen = false, bool coreMode = false, bool openGLScreen = true);

	void ClearBuffer();
	void SwapBuffer();

public:

	int GetWidth();
	int GetHeight();

private:

	bool SetupWindow(const std::string& windowTitle, int width,
					 int height, bool fullscreen, bool openGLScreen);

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(Screen&);

private:

	SDL_Window* m_window;
	SDL_GLContext m_context;

	int m_width;
	int m_height;

};

