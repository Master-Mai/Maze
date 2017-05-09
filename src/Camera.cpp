#include "Camera.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

Camera::Camera() {
    isFirst = true;
    sensitivity = 1.0;
    pfov = 45.0, pratio = 1.0, pnear = 0.1, pfar = 20.0;
    cpitch = cyaw = 0.0;
    cameraX = 0.0;
    cameraY = 0.0;
    cameraZ = 2.0;
}

void Camera::init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(pfov, pratio, pnear, pfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
}

/* �����ǰ�ơ�
*  distance - �ƶ�����
*/
void Camera::moveForward(double const distance)
{
	cameraX -= distance * sin(radian(cyaw));
	cameraZ -= distance * cos(radian(cyaw));
}

/* ��������ơ�
*  distance - �ƶ�����
*/
void Camera::moveBack(double const distance)
{
    cameraX += distance * sin(radian(cyaw));
    cameraZ += distance * cos(radian(cyaw));
}

/* ��������ơ�
*  distance - �ƶ�����
*/
void Camera::moveLeft(double const distance)
{
    cameraX -= distance * cos(radian(cyaw));
    cameraZ += distance * sin(radian(cyaw));
}

/* ��������ơ�
*  distance - �ƶ�����
*/
void Camera::moveRight(double const distance)
{
    cameraX += distance * cos(radian(cyaw));
    cameraZ -= distance * sin(radian(cyaw));
}

/* ��ת�������
*  pitch - ������
*  yaw   - ƫ����
*/
void Camera::rotate(double const pitch, double const yaw)
{
    cpitch = pitch;
    cyaw = yaw;
    if (cpitch > 90.0) cpitch = 90.0;
    else if (cpitch < -90.0) cpitch = -90.0;
}

/* �����ӳ��� */
void Camera::setFOV(double fov)
{
    pfov = fov;
}

/* ���û��泤��� */
void Camera::setAspectRatio(double ratio)
{
    pratio = ratio;
}

void Camera::setSensitivity(double s)
{
    sensitivity = s;
}

/* �����������ʼ��λ�á�
*  (x, y, z) - �������
*/
void Camera::setPosition(double x, double y, double z)
{
    cameraX = x;
    cameraY = y;
    cameraZ = z;
}

/* ��������Ƕ� */
void Camera::updateDirection(double const mouseX, double const mouseY)
{
    if (isFirst) {
        isFirst = false;
        originX = mouseX;
        originY = mouseY;
    }
    rotate((mouseY - originY) * sensitivity, (originX - mouseX) * sensitivity);
}

/* �������λ�� */
void Camera::updatePosition()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ,
              cameraX - sin(radian(cyaw)) * cos(radian(cpitch)),
              cameraY - sin(radian(cpitch)),
              cameraZ - cos(radian(cyaw)) * cos(radian(cpitch)),
              0, 1, 0);
}

/* �Ƕ�ת���� */
double Camera::radian(double degree)
{
	return degree * PI / 180.0;
}
