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
	// YU ����ϵ��������1����С��1��
	// dx,dy,dzΪ����
	void draw(int YU, int dx, int dy, int dz);

private:
	vector<V> VList;  // ����
	vector<VT> VTList; // ��������
	vector<VN> VNList; // ������
	vector<F> FList; // ��
};

#endif // !_OBJ3DMODEL_H_