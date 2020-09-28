#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <SDL.h>
#include <string>
#include <map>

class Screen
{
public:

	static Screen* Instance();

public:

	bool Initialize();
	void Shutdown();

public:

	bool& IsRunning();
	SDL_Window* GetWindow();

private:

	bool SetupWindow();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(Screen&);

private:


	bool m_isRunning;
	SDL_Window* m_window;
	SDL_GLContext m_context;

	std::map<std::string, std::string> m_settings;

};

