#include "MainScene.h"
#include "SnowParticle.h"
#include <GLFW/glfw3.h>

/* ????3D???? */
Model island("resources/model/low-poly-mill.obj", false);
SnowParticle snowParticle;

void MainScene::init() {
	/* ?ик?????? */

	island.init(0.0, -4.0, 2.0, 0.1);
	snowParticle.init();
}

void MainScene::update()
{
	island.draw();
	snowParticle.DrawParticle();
}