#include "obj3dmodel.h"

obj3dmodel::obj3dmodel(const char* filename)
{
	parse(filename);
}

obj3dmodel::~obj3dmodel()
{
}

void obj3dmodel::parse(const char * filename)
{
	ifstream ifs(filename);
	string s;
	F *f;
	V *v;
	VN *vn;
	VT *vt;
	while (getline(ifs, s)) {
		if (s.length() < 2) continue;
		if (s[0] == 'v') {
			if (s[1] == 't') { // vt 0.581151 0.979929 纹理
				istringstream in(s);
				vt = new VT();
				string head;
				in >> head >> vt->TU >> vt->TV;
				VTList.push_back(*vt);
			}
			else if (s[1] == 'n') { // vn 0.637005 -0.0421857 0.769705 法向量
				istringstream in(s);
				vn = new VN();
				string head;
				in >> head >> vn->NX >> vn->NY >> vn->NZ;
				VNList.push_back(*vn);
			}
			else { // v -53.0413 158.84 -135.806 点
				istringstream in(s);
				v = new V();
				string head;
				in >> head >> v->X >> v->Y >> v->Z;
				VList.push_back(*v);
			}
		}
		else if (s[0] == 'f') { // f 7/9/21 1/10/22 5/11/23 面
			for (int i = s.size() - 1; i >= 0; i--) {
				if (s[i] == '/') s[i] = ' ';
			}
			istringstream in(s);
			f = new F();
			string head;
			in >> head;
			for (int i = 0; i < 3; i++) {
				if (VList.size() != 0) {
					in >> f->V[i];
					f->V[i] -= 1;
				}
				if (VTList.size() != 0) {
					in >> f->T[i];
					f->T[i] -= 1;
				}
				if (VNList.size() != 0) {
					in >> f->N[i];
					f->N[i] -= 1;
				}
			}
			FList.push_back(*f);
		}
	}
}

void obj3dmodel::draw(int YU, int dx, int dy, int dz)
{
	for (int i = 0; i < FList.size(); i++)
	{
		glBegin(GL_TRIANGLES); // 绘制三角形GL_TRIANGLES;GL_LINE_LOOP;GL_LINES;GL_POINTS
		if (VTList.size() != 0) glTexCoord2f(VTList[FList[i].T[0]].TU, VTList[FList[i].T[0]].TV); // 纹理
		if (VNList.size() != 0) glNormal3f(VNList[FList[i].N[0]].NX, VNList[FList[i].N[0]].NY, VNList[FList[i].N[0]].NZ); // 法向量
		glVertex3f(VList[FList[i].V[0]].X / YU + dx, VList[FList[i].V[0]].Y / YU + dy, VList[FList[i].V[0]].Z / YU + dz); // 上顶点

		if (VTList.size() != 0) glTexCoord2f(VTList[FList[i].T[1]].TU, VTList[FList[i].T[1]].TV); // 纹理
		if (VNList.size() != 0) glNormal3f(VNList[FList[i].N[1]].NX, VNList[FList[i].N[1]].NY, VNList[FList[i].N[1]].NZ); // 法向量
		glVertex3f(VList[FList[i].V[1]].X / YU + dx, VList[FList[i].V[1]].Y / YU + dy, VList[FList[i].V[1]].Z / YU + dz); // 左下

		if (VTList.size() != 0) glTexCoord2f(VTList[FList[i].T[2]].TU, VTList[FList[i].T[2]].TV); // 纹理
		if (VNList.size() != 0) glNormal3f(VNList[FList[i].N[2]].NX, VNList[FList[i].N[2]].NY, VNList[FList[i].N[2]].NZ); // 法向量
		glVertex3f(VList[FList[i].V[2]].X / YU + dx, VList[FList[i].V[2]].Y / YU + dy, VList[FList[i].V[2]].Z / YU + dz); // 上顶点

		glEnd(); // 三角形绘制结束
	}
}
