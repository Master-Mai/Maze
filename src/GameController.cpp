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

/* �������λ�� */
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

/* ������Ϸ���ڡ�
*  w - ���ڿ��
*  h - ���ڸ߶�
*  t - ���ڱ���
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

/* ����OpenGL����ʼ��������á� */
void GameController::initOpenGLContext()
{
    memset(keys, 0, sizeof(keys));

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    camera = new Camera();
    camera->setAspectRatio((double)width / height);
    camera->setSensitivity(1.0);
    camera->setPosition(0.0, 0.0, 2.0);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* ��Ȳ��� */
    glEnable(GL_DEPTH_TEST);

    /* ����� */
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH_HINT);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera->init();

    /* ������Ϸ���� */
    scene = new MainScene();
    scene->init();
}

/* ��Ϸ��ѭ�� */
void GameController::run()
{
    int counter = 0;
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

/* ���ĳ�������Ƿ��� */
bool GameController::keyPressed(int keyCode)
{
    return keys[keyCode];
}

/* �ر���Ϸ���� */
void GameController::close()
{
    glfwDestroyWindow(window);
}

/* �����¼��ص� */
void GameController::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) instance->keys[key] = true;

    if (action == GLFW_RELEASE) instance->keys[key] = false;
}

/* ����ƶ��¼��ص� */
void GameController::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
    instance->camera->updateDirection(xpos, ypos);
}
