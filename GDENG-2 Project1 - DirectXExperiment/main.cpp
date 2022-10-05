#include "AppWindow.h"
#include "GameWindow.h"

int main() {

	
	AppWindow::initialize();
	//GameWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	//GameWindow* runningGame = (GameWindow*)GameWindow::getInstance();
	runningApp->initializeEngine();
	//runningGame->CreateGameWindow();
	while(runningApp->isRun())
	{
		runningApp->broadcast();
		//runningGame->broadcast();
	}

	return 0;
}