#include "AppWindow.h"

int main() {
	
	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	runningApp->initializeEngine();
	runningApp->createInterface();
	while(runningApp->isRun())
	{
		runningApp->broadcast();
	}

	return 0;
}