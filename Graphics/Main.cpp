#include "App.h"
#include "SDL.h"

int main(int argc, char* args[])
{
	App* app = new App();

	app->Initialize();

	while (app->IsRunning())
	{
		app->Update();
		app->Draw();
	}

	app->Exit();

	return 0;
}