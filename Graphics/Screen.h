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
	bool Initialize(const std::string& windowTitle, int width, int height,
					bool fullscreen = false, bool coreMode = false, bool openGLScreen = true);

	void ClearBuffer();
	void SwapBuffer();
	void DisplayProfile();
	void DisplayExtensions();
	void ResizeWindow(int width, int height);

public:

	void SetScreenColor(float r, float g, float b, float a);
	void SetOutlineMode(bool flag);
	void SetScreen2D();
	void SetScreen3D(float fov = 45.0f, float nearClip = 0.1f, float farClip = 500.0f);
	void SetZoom(float fov);

	int GetWidth();
	int GetHeight();

	bool IsOutlineMode();

private:

	bool SetupWindow(const std::string& windowTitle, int width,
					 int height, bool fullscreen, bool openGLScreen);

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(Screen&);

private:

	int m_width;
	int m_height;

	float m_fov;
	float m_nearClip;
	float m_farClip;
	
	bool m_isOutlineMode;

	glm::mat4 m_projection;

	SDL_Window* m_window;
	SDL_GLContext m_context;

};

