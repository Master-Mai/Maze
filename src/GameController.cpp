#include "GameController.h"
#include "MainScene.h"
#include "Model.h"

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

/* 处理键盘事件 */
void GameController::handleKeyboardEvents()
{
    /* 更新相机位置 */
    double vel = 0.001;
    if (keyPressed(GLFW_KEY_W)) camera->moveForward(vel);
    if (keyPressed(GLFW_KEY_S)) camera->moveBack(vel);
    if (keyPressed(GLFW_KEY_A)) camera->moveLeft(vel);
    if (keyPressed(GLFW_KEY_D)) camera->moveRight(vel);
    camera->updatePosition();

    /* 其他键盘事件处理 */
    if (keyPressed(GLFW_KEY_ESCAPE)) {
        glfwTerminate();
        exit(0);
    }
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
    camera->setOrigin(width / 2.0, height / 2.0);
    camera->setAspectRatio((double)width / height);
    camera->setSensitivity(1.0);
    camera->setPosition(0.0, 0.0, 10.0);
    
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* 深度测试 */
    glEnable(GL_DEPTH_TEST);

    /* 抗锯齿 */
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH_HINT);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera->init();

    /* 设置游戏场景 */
    scene = new MainScene();
    scene->init();

    glfwSetCursorPos(window, instance->width / 2.0, instance->height / 2.0);
}

/* 游戏主循环 */
void GameController::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->update();

        handleKeyboardEvents();

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
    glfwSetCursorPos(window, instance->width / 2.0, instance->height / 2.0);
}
