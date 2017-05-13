#include "MainScene.h"
#include <GLFW/glfw3.h>

/* 导入3D模型-英雄 */
obj3dmodel hero(".\\resources\\model\\boy.obj");

void drawCube(GLfloat ox, GLfloat oy, GLfloat oz, GLfloat length) {
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(ox, oy, oz);
    glVertex3f(ox, oy + length, oz);
    glVertex3f(ox + length, oy + length, oz);
    glVertex3f(ox + length, oy, oz);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(ox, oy, oz + length);
    glVertex3f(ox, oy + length, oz + length);
    glVertex3f(ox + length, oy + length, oz + length);
    glVertex3f(ox + length, oy, oz + length);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(ox, oy, oz);
    glVertex3f(ox, oy, oz + length);
    glVertex3f(ox + length, oy, oz + length);
    glVertex3f(ox + length, oy, oz);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(ox, oy + length, oz);
    glVertex3f(ox, oy + length, oz + length);
    glVertex3f(ox + length, oy + length, oz + length);
    glVertex3f(ox + length, oy + length, oz);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(ox, oy, oz);
    glVertex3f(ox, oy, oz + length);
    glVertex3f(ox, oy + length, oz + length);
    glVertex3f(ox, oy + length, oz);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(ox + length, oy, oz);
    glVertex3f(ox + length, oy, oz + length);
    glVertex3f(ox + length, oy + length, oz + length);
    glVertex3f(ox + length, oy + length, oz);
    glEnd();
}

void MainScene::update()
{
    drawCube(-0.05f, -0.05f, -0.05f, 0.1f);
    drawCube(-2.5f, -6.0f, -2.5f, 5.0f);
	hero.draw(6, -1, -1, -1);
}
