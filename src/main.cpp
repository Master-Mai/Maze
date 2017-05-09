#include "GameController.h"
#include "Camera.h"
#include <iostream>


int main(void)
{
    GameController *controller = GameController::getInstance();
    controller->createWindow(1024, 768, "Test");
    controller->initOpenGLContext();
    controller->run();

	return 0;
}