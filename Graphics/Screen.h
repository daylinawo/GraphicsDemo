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

	bool Initialize(const std::string& windowTitle, int width, int height,
					bool fullscreen = false, bool coreMode = false, bool openGLScreen = true);
	void Shutdown();

public:

	void SwapBuffer();

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

	std::map<std::string, std::string> m_settings;

};

