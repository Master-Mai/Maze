#ifndef _OBJ3DMODEL_H_
#define _OBJ3DMODEL_H_

#include <vector> 
#include <string>
#include <fstream>
#include <sstream>
#include <GL\freeglut.h>
using namespace std;

struct V {
	double X;
	double Y;
	double Z;
};
struct VT {
	double TU;
	double TV;
};
struct VN {
	double NX;
	double NY;
	double NZ;
};
struct F { // f Vertex1/Texture1/Normal1 Vertex2/Texture2/Normal2 Vertex3/Texture3/Normal3
	int V[3];
	int T[3];
	int N[3];
};

class obj3dmodel
{
public:
	obj3dmodel(const char* filename);
	~obj3dmodel();
	void parse(const char* filename);
	// YU 缩放系数，大于1缩，小于1放
	// dx,dy,dz为坐标
	void draw(int YU, int dx, int dy, int dz);

private:
	vector<V> VList;  // 顶点
	vector<VT> VTList; // 纹理坐标
	vector<VN> VNList; // 法向量
	vector<F> FList; // 面
};

#endif // !_OBJ3DMODEL_H_