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
	void DisplayProfile();
	void DisplayExtensions();

	void SetOutlineMode(bool flag);
	bool IsOutlineMode();

public:

	void SetScreenColor(float r, float g, float b, float a);
	int GetWidth();
	int GetHeight();

	void ResizeWindow(int width, int height);

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

	bool m_isOutlineMode;

};

