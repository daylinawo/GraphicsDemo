#pragma once

#include "Input.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "Screen.h"

class App
{
public:

	App();

public:

	bool Initialize();
	void Run();
	void Exit();

public:

	bool IsRunning();

private:
	Renderer* m_renderer;
	bool m_isRunning;
	int m_lastTime;
};

