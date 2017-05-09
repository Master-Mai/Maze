#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <GLFW/glfw3.h>
#include <string>
#include "Scene.h"
#include "Camera.h"

class GameController {
public:
    static GameController *getInstance();
    void createWindow(int w, int h, std::string t);
    void initOpenGLContext();
    void run();
    bool keyPressed(int key);
    void close();

private:
    static GameController *instance;
    GLFWwindow* window;
    Camera *camera;
    Scene *scene;
    int height, width;
    std::string title;
    bool keys[512];

    GameController();
    ~GameController();
    void updateCamera();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif // !GAME_CONTROLLER_H
