#ifndef _MODEL_H_
#define _MODEL_H_

#include <map> 
#include <string>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/DefaultLogger.hpp"
#include "assimp/LogStream.hpp"
#include <assimp/cimport.h>

class Model
{
public:
    Model(std::string filename, bool t);
    ~Model();
    void draw();
    bool Import3DFromFile(const std::string& pFile);
    std::string getBasePath(const std::string& path);
    int LoadGLTextures(const aiScene* scene);
    void init(double x = 0.0, double y = 0.0, double z = 0.0, double factor = 1.0);
    void Color4f(const aiColor4D *color);
    void set_float4(float f[4], float a, float b, float c, float d);
    void color4_to_float4(const aiColor4D *c, float f[4]);
    void apply_material(const aiMaterial *mtl);
    void recursive_render(const struct aiScene *sc, const struct aiNode* nd, float scale, float x, float y, float z);
    void drawAiScene(const aiScene* scene, double factor, double x, double y, double z);
    void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo);
    void get_bounding_box(aiVector3D* min, aiVector3D* max);

private:
    const aiScene* scene = NULL;
    GLuint scene_list = 0;
    aiVector3D scene_min, scene_max, scene_center;
    std::map<std::string, GLuint*> textureIdMap;
    std::string path;
    GLuint* textureIds;	
    Assimp::Importer importer;
    GLuint listIndex;
    bool loadTexture;
};

#endif // !_OBJ3DMODEL_H_