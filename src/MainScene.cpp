#include "MainScene.h"
#include <GLFW/glfw3.h>

/* 导入3D模型 */
Model boy("resources/model/boy.obj");
Model monkey("resources/model/monkey.obj");

void MainScene::init() {
    /* 添加光源 */
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    boy.compile(-1.0, -1.0, -1.0);
    monkey.compile(1.0, 1.0, 1.0);
}

void MainScene::update()
{
    boy.draw();
    monkey.draw();
}
