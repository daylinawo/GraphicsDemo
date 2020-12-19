#pragma once

#include "glad.h"

#include <map>
#include <SDL.h>
#include <string>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

class Screen
{
public:

	static Screen* Instance();

public:

	void Shutdown();
	bool Initialize(const std::string& windowTitle, int width, int height, bool fullscreen, bool coreMode = false);

	void ClearBuffer();
	void SwapBuffer();
	void DisplayProfile();
	void DisplayExtensions();
	void ResizeWindow(int width, int height);

public:

	glm::vec2 GetResolution();

	void SetScreenColor(float r, float g, float b, float a);
	void SetOutlineMode(bool flag);
	void SetScreen2D();
	void SetScreen3D(GLfloat fov = 45.0f, GLfloat nearClip = 0.1f, GLfloat = 500.0f);

	bool IsOutlineMode();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(Screen&);

private:

	int m_width;
	int m_height;
	
	bool m_isOutlineMode;

	glm::mat4 m_projection;

	SDL_Window* m_window;
	SDL_GLContext m_context;

};

