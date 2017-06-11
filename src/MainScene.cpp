#include "MainScene.h"
#include "SnowParticle.h"
#include <GLFW/glfw3.h>

/* 导入3D模型 */
Model island("resources/model/low-poly-mill.obj", false);
SnowParticle snowParticle;

void MainScene::init() {
    /* 添加光源 */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    /* XXX docs say all polygons are emitted CCW, but tests show that some aren't. */
    if (getenv("MODEL_IS_BROKEN"))
        glFrontFace(GL_CW);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClearDepth(1.0f);				// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation


    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);

    GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[] = { 0.0f, 0.0f, 15.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT1);

    island.init(0.0, -4.0, 2.0, 0.1);
    snowParticle.init();
}

void MainScene::update()
{
    island.draw();
    snowParticle.DrawParticle();
}