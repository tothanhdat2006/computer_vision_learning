#include "App.h"

int main()
{
	App *app = new App();
	app->running();
	delete app;
	return 0;
}