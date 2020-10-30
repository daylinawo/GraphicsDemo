#include "App.h"

int main(int argc, char* args[])
{
	App* app = new App();

	app->Initialize();

	while (app->IsRunning())
	{
		app->Run();
	}

	app->Exit();

	return 0;
}