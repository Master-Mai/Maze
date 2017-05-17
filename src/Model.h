#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector> 
#include <string>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>

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

class Model
{
public:
    Model(const char* filename);
    ~Model();
    void parse(const char* filename);
    void compile(double dx, double dy, double dz, double YU = 1.0);
    void draw();

private:
    std::vector<V> VList;  // ����
    std::vector<VT> VTList; // ��������
    std::vector<VN> VNList; // ������
    std::vector<F> FList; // ��
    GLuint listIndex;
};

#endif // !_OBJ3DMODEL_H_