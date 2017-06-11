#include "Camera.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

Camera::Camera() {
    isFirst = true;
    sensitivity = 1.0;
    pfov = 45.0, pratio = 1.0, pnear = 0.1, pfar = 1000.0;
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

/* 摄像机前移。
*  distance - 移动距离
*/
void Camera::moveForward(double const distance)
{
    cameraX -= distance * sin(radian(cyaw));
    cameraZ -= distance * cos(radian(cyaw));
}

/* 摄像机后移。
*  distance - 移动距离
*/
void Camera::moveBack(double const distance)
{
    cameraX += distance * sin(radian(cyaw));
    cameraZ += distance * cos(radian(cyaw));
}

/* 摄像机左移。
*  distance - 移动距离
*/
void Camera::moveLeft(double const distance)
{
    cameraX -= distance * cos(radian(cyaw));
    cameraZ += distance * sin(radian(cyaw));
}

/* 摄像机右移。
*  distance - 移动距离
*/
void Camera::moveRight(double const distance)
{
    cameraX += distance * cos(radian(cyaw));
    cameraZ -= distance * sin(radian(cyaw));
}

/* 旋转摄像机。
*  pitch - 俯仰角
*  yaw   - 偏航角
*/
void Camera::rotate(double const pitch, double const yaw)
{
    cpitch = pitch;
    cyaw = yaw;
    if (cpitch > 89.9) cpitch = 89.9;
    else if (cpitch < -89.9) cpitch = -89.9;
}

/* 设置视场角 */
void Camera::setFOV(double fov)
{
    pfov = fov;
}

/* 设置画面长宽比 */
void Camera::setAspectRatio(double ratio)
{
    pratio = ratio;
}

void Camera::setSensitivity(double s)
{
    sensitivity = s;
}

/* 设置相机（初始）位置。
*  (x, y, z) - 相机坐标
*/
void Camera::setPosition(double x, double y, double z)
{
    cameraX = x;
    cameraY = y;
    cameraZ = z;
}

/* 更新相机角度 */
void Camera::updateDirection(double const mouseX, double const mouseY)
{
    if (isFirst) {
        isFirst = false;
        originX = mouseX;
        originY = mouseY;
    }
    rotate((mouseY - originY) * sensitivity, (originX - mouseX) * sensitivity);
}

/* 更新相机位置 */
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

/* 角度转弧度 */
double Camera::radian(double degree)
{
    return degree * PI / 180.0;
}
