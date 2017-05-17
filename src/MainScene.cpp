#include "MainScene.h"
#include <GLFW/glfw3.h>

/* 导入3D模型 */
Model boy("resources/model/boy.obj");
Model monkey("resources/model/monkey.obj");

void MainScene::init() {
    /* 添加光源 */
    glEnable(GL_LIGHTING);
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHT0);
    /*glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);*/

    boy.compile(-1.0, -1.0, -1.0);
    monkey.compile(1.0, 1.0, 1.0);
}

void MainScene::update()
{
    boy.draw();
    monkey.draw();
}
