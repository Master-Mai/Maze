#include "GameController.h"
#include "MainScene.h"

GameController* GameController::instance = new GameController();

GameController::GameController() {
    width = 1024;
    height = 768;
    title = "Game";
}

GameController::~GameController()
{
    delete camera;
    delete scene;
}

/* 更新相机位置 */
void GameController::updateCamera()
{
    double vel = 0.001;
    if (keyPressed(GLFW_KEY_W)) camera->moveForward(vel);
    if (keyPressed(GLFW_KEY_S)) camera->moveBack(vel);
    if (keyPressed(GLFW_KEY_A)) camera->moveLeft(vel);
    if (keyPressed(GLFW_KEY_D)) camera->moveRight(vel);
    camera->updatePosition();
}

GameController * GameController::getInstance()
{
    return instance;
}

/* 创建游戏窗口。
*  w - 窗口宽度
*  h - 窗口高度
*  t - 窗口标题
*/
void GameController::createWindow(int w, int h, std::string t)
{
    width = w;
    height = h;
    title = t;

    if (!glfwInit())
        exit(-1);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }
}

/* 启用OpenGL，初始化相关设置。 */
void GameController::initOpenGLContext()
{
    memset(keys, 0, sizeof(keys));
    camera = new Camera();
    camera->setAspectRatio((double)width / height);
    camera->setSensitivity(1.0);
    camera->setPosition(0.0, 0.0, 2.0);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    camera->init();

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
}

/* 游戏主循环 */
void GameController::run()
{
    /* 设置游戏场景 */
    scene = new MainScene();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->update();

        updateCamera();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

/* 检测某个按键是否按下 */
bool GameController::keyPressed(int keyCode)
{
    return keys[keyCode];
}

/* 关闭游戏窗口 */
void GameController::close()
{
    glfwDestroyWindow(window);
}

/* 键盘事件回调 */
void GameController::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) instance->keys[key] = true;

    if (action == GLFW_RELEASE) instance->keys[key] = false;
}

/* 鼠标移动事件回调 */
void GameController::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
    instance->camera->updateDirection(xpos, ypos);
}
