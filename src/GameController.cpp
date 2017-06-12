#include "GameController.h"
#include "MainScene.h"
#include "Model.h"

//天空盒
#include <Windows.h>  
#include <gl/GLU.h>  

#include <gl/glaux.h>  
#include <GL/glut.h>  
#include <stdio.h>  
static GLuint texName[7];

AUX_RGBImageRec * imageRec[6];
AUX_RGBImageRec * CreateTextureFromBmp(int i)
{
	FILE *File = NULL;
	char *Filename;
	switch (i)
	{
	case 0:
		Filename = "Skybox/1.bmp";
		break;
	case 1:
		Filename = "Skybox/2.bmp";
		break;
	case 2:
		Filename = "Skybox/3.bmp";
		break;
	case 3:
		Filename = "Skybox/4.bmp";
		break;
	case 4:
		Filename = "Skybox/5.bmp";
		break;
	case 5:
		Filename = "Skybox/6.bmp";
		break;
	default:
		break;
	}

	File = fopen(Filename, "r");
	if (!File)
		return 0;
	fclose(File);
	return auxDIBImageLoad(Filename);

}
void drawSkybox(){
	for (int i = 0; i <= 5; i++){
		
		glEnable(GL_TEXTURE_2D);
		
		int x = 0, y = 0, z = 0;
		int height = 200, width = 200, length = 200;
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		switch (i)
		{
		case 0:
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x - width, y + height, z + length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y - height, z + length);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y - height, z + length);
			glEnd();
			break;
		case 1:
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y - height, z - length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z - length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width, y + height, z - length);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width, y - height, z - length);
			glEnd();
			break;
		case 2:
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + length, y - height, z + height);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + length, y + height, z + height);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x + length, y + height, z - height);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x + length, y - height, z - height);
			glEnd();
			break;
		case 3:
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x - length, y + height, z - height);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x - length, y + height, z + height);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x - length, y - height, z + height);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x - length, y - height, z - height);
			glEnd();
			break;
		case 4:
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + length, y + length, z - height);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + length, y + length, z + height);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x - length, y + length, z + height);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x - length, y + length, z - height);
			glEnd();
			break;
		case 5:
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + length, y - length, z - height);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + length, y - length, z + height);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x - length, y - length, z + height);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x - length, y - length, z - height);
			glEnd();
			glFlush();
			break;
		default:
			break;
		}


	}
}
//天空盒
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
	double vel = 0.005;
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
	
	for (int i = 0; i <= 5; i++){
		imageRec[i] = CreateTextureFromBmp(i);
		if (!imageRec)
			exit(EXIT_FAILURE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &texName[i]);
		glBindTexture(GL_TEXTURE_2D, texName[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageRec[i]->sizeX, imageRec[i]->sizeX,
			0, GL_RGB, GL_UNSIGNED_BYTE, imageRec[i]->data);
	}
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
		drawSkybox();
		glEnable(GL_LIGHTING);

		glEnable(GL_LIGHT0);

		glEnable(GL_NORMALIZE);
		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);		 
		glClearDepth(1.0f);				// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation


		glEnable(GL_NORMALIZE);

		GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[] = { 0.0f, 0.0f, -1115.0f, 1.0f };
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
		glEnable(GL_LIGHT1);
		GLfloat lLightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat lLightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat lLightPosition[] = { 0.0f, 0.0f, 1115.0f, 1.0f };
		glLightfv(GL_LIGHT2, GL_AMBIENT, lLightAmbient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lLightDiffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, lLightPosition);
		glEnable(GL_LIGHT2);

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