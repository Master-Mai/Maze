#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.14159265359

class Camera {
public:
	Camera();
	void init();
	void moveForward(double const distance);
	void moveBack(double const distance);
	void moveLeft(double const distance);
	void moveRight(double const distance);
	void rotate(double const pitch, double const yaw);
    void setFOV(double fov);
    void setAspectRatio(double ratio);
    void setSensitivity(double s);
    void setPosition(double x, double y, double z);
	void updateDirection(double const mouseX, double const mouseY);
    void updatePosition();

private:
    bool isFirst;
    double originX, originY;
    double sensitivity;
	double pfov, pratio, pnear, pfar;
	double cpitch, cyaw;
	double cameraX, cameraY, cameraZ;

	inline double radian(double degree);
};

#endif // !CAMERA_H
