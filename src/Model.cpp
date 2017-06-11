#include <gl/glew.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <iostream>
#include "Model.h"

#define aisgl_min(x, y) (x < y ? x : y)
#define aisgl_max(x, y) (y > x ? y : x)

Model::Model(std::string filename)
{
    Import3DFromFile(filename);
    path = filename;
    init(0.0);
}

Model::~Model()
{
    textureIdMap.clear();

    if (textureIds)
    {
        delete[] textureIds;
        textureIds = NULL;
    }
}

void Model::draw()
{
    glCallList(listIndex);
}

bool Model::Import3DFromFile(const std::string& pFile)
{
    // Check if file exists
    std::ifstream fin(pFile.c_str());
    if (!fin.fail())
    {
        fin.close();
    }
    else
    {
        //MessageBox(NULL, ("Couldn't open file: " + pFile).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);

    // If the import failed, report it
    if (!scene) {
        return false;
    } else {
        get_bounding_box(&scene_min, &scene_max);
        scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
        scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
        scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
        
        return true;
    }
}

std::string Model::getBasePath(const std::string& path)
{
    size_t pos = path.find_last_of("\\/");
    return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

int Model::LoadGLTextures(const aiScene* scene)
{
    ILboolean success;

    /* Before calling ilInit() version should be checked. */
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
    {
        /// wrong DevIL version ///
        std::string err_msg = "Wrong DevIL version. Old devil.dll in system32/SysWow64?";
        char* cErr_msg = (char *)err_msg.c_str();
        return -1;
    }

    ilInit(); /* Initialization of DevIL */

    /* getTexture Filenames and Numb of Textures */
    for (unsigned int m = 0; m<scene->mNumMaterials; m++)
    {
        int texIndex = 0;
        aiReturn texFound = AI_SUCCESS;

        aiString path;	// filename

        while (texFound == AI_SUCCESS)
        {
            texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
            textureIdMap[path.data] = NULL; //fill map with textures, pointers still NULL yet
            texIndex++;
        }
    }

    int numTextures = textureIdMap.size();

    /* array with DevIL image IDs */
    ILuint* imageIds = NULL;
    imageIds = new ILuint[numTextures];

    /* generate DevIL Image IDs */
    ilGenImages(numTextures, imageIds); /* Generation of numTextures image names */

                                        /* create and fill array with GL texture ids */
    textureIds = new GLuint[numTextures];
    glGenTextures(numTextures, textureIds); /* Texture name generation */

                                            /* get iterator */
    std::map<std::string, GLuint*>::iterator itr = textureIdMap.begin();

    std::string basepath = getBasePath(path);
    for (int i = 0; i<numTextures; i++)
    {

        //save IL image ID
        std::string filename = (*itr).first;  // get filename
        (*itr).second = &textureIds[i];	  // save texture id for filename in map
        itr++;								  // next texture


        ilBindImage(imageIds[i]); /* Binding of DevIL image name */
        std::string fileloc = basepath + filename;	/* Loading of image */
        success = ilLoadImage(fileloc.c_str());

        if (success) /* If no error occurred: */
        {
            // Convert every colour component into unsigned byte.If your image contains 
            // alpha channel you can replace IL_RGB with IL_RGBA
            success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
            if (!success)
            {
                return -1;
            }
            // Binding of texture name
            glBindTexture(GL_TEXTURE_2D, textureIds[i]);
            // redefine standard texture values
            // We will use linear interpolation for magnification filter
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // We will use linear interpolation for minifying filter
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            // Texture specification
            glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
                ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
                ilGetData());
            // we also want to be able to deal with odd texture dimensions
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
            glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        }
        else
        {
            /* Error occurred */
            //MessageBox(NULL, ("Couldn't load Image: " + fileloc).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION);
        }
    }
    // Because we have already copied image data into texture data  we can release memory used by image.
    ilDeleteImages(numTextures, imageIds);

    // Cleanup
    delete[] imageIds;
    imageIds = NULL;

    return true;
}

// All Setup For OpenGL goes here
void Model::init(double x, double y, double z, double factor)
{
    LoadGLTextures(scene);
    drawAiScene(scene, factor, x, y, z);
}


// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
void Model::Color4f(const aiColor4D *color)
{
    glColor4f(color->r, color->g, color->b, color->a);
}

void Model::set_float4(float f[4], float a, float b, float c, float d)
{
    f[0] = a;
    f[1] = b;
    f[2] = c;
    f[3] = d;
}

void Model::color4_to_float4(const aiColor4D *c, float f[4])
{
    f[0] = c->r;
    f[1] = c->g;
    f[2] = c->b;
    f[3] = c->a;
}

void Model::apply_material(const aiMaterial *mtl)
{
    float c[4];

    GLenum fill_mode;
    int ret1, ret2;
    aiColor4D diffuse;
    aiColor4D specular;
    aiColor4D ambient;
    aiColor4D emission;
    float shininess, strength;
    int two_sided;
    int wireframe;
    unsigned int max;	// changed: to unsigned

    int texIndex = 0;
    aiString texPath;	//contains filename of texture

    if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
    {
        //bind texture
        unsigned int texId = *textureIdMap[texPath.data];
        glBindTexture(GL_TEXTURE_2D, texId);
    }

    set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        color4_to_float4(&diffuse, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        color4_to_float4(&specular, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

    set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        color4_to_float4(&ambient, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
        color4_to_float4(&emission, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

    max = 1;
    ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    max = 1;
    ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
    if ((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
    else {
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
        set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
    }

    max = 1;
    if (AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
        fill_mode = wireframe ? GL_LINE : GL_FILL;
    else
        fill_mode = GL_FILL;
    glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

    max = 1;
    if ((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}

void Model::get_bounding_box_for_node(const aiNode* nd,
                               aiVector3D* min,
                               aiVector3D* max,
                               aiMatrix4x4* trafo) {
    aiMatrix4x4 prev;
    unsigned int n = 0, t;

    prev = *trafo;
    aiMultiplyMatrix4(trafo, &nd->mTransformation);

    for (; n < nd->mNumMeshes; ++n) {
        const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
        for (t = 0; t < mesh->mNumVertices; ++t) {

            aiVector3D tmp = mesh->mVertices[t];
            aiTransformVecByMatrix4(&tmp, trafo);

            min->x = aisgl_min(min->x, tmp.x);
            min->y = aisgl_min(min->y, tmp.y);
            min->z = aisgl_min(min->z, tmp.z);

            max->x = aisgl_max(max->x, tmp.x);
            max->y = aisgl_max(max->y, tmp.y);
            max->z = aisgl_max(max->z, tmp.z);
        }
    }

    for (n = 0; n < nd->mNumChildren; ++n) {
        get_bounding_box_for_node(nd->mChildren[n], min, max, trafo);
    }
    *trafo = prev;
}

void Model::get_bounding_box(aiVector3D* min, aiVector3D* max)
{
    aiMatrix4x4 trafo;
    aiIdentityMatrix4(&trafo);

    min->x = min->y = min->z = 1e10f;
    max->x = max->y = max->z = -1e10f;
    get_bounding_box_for_node(scene->mRootNode, min, max, &trafo);
}

void Model::recursive_render(const struct aiScene *sc, const struct aiNode* nd, float scale, float x, float y, float z)
{
    unsigned int i;
    unsigned int n = 0, t;
    /*aiMatrix4x4 m = nd->mTransformation;

    aiMatrix4x4 m2;
    aiMatrix4x4::Translation(scene_center, m2);

    aiMatrix4x4 m3;
    aiMatrix4x4::Scaling(aiVector3D(scale, scale, scale), m3);

    aiMatrix4x4 m4;
    aiMatrix4x4::Translation(aiVector3D(0, 0, 200), m4);

    m = m * m2 * m3 * m4;*/

    // update transform
    //m.Transpose();
    glPushMatrix();
    //glMultMatrixf((float*)&m);

    // draw all meshes assigned to this node
    for (; n < nd->mNumMeshes; ++n)
    {
        const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

        apply_material(sc->mMaterials[mesh->mMaterialIndex]);


        if (mesh->mNormals == NULL)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }

        if (mesh->mColors[0] != NULL)
        {
            glEnable(GL_COLOR_MATERIAL);
        }
        else
        {
            glDisable(GL_COLOR_MATERIAL);
        }

        for (t = 0; t < mesh->mNumFaces; ++t) {
            const struct aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch (face->mNumIndices)
            {
            case 1: face_mode = GL_POINTS; break;
            case 2: face_mode = GL_LINES; break;
            case 3: face_mode = GL_TRIANGLES; break;
            default: face_mode = GL_POLYGON; break;
            }

            glBegin(face_mode);

            for (i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
            {
                int vertexIndex = face->mIndices[i];	// get group index for current index
                if (mesh->mColors[0] != NULL)
                    Color4f(&mesh->mColors[0][vertexIndex]);
                if (mesh->mNormals != NULL)

                    if (mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
                    {
                        glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
                    }

                glNormal3fv(&mesh->mNormals[vertexIndex].x);
                glVertex3f(mesh->mVertices[vertexIndex].x * scale + x,
                    mesh->mVertices[vertexIndex].y * scale + y,
                    mesh->mVertices[vertexIndex].z * scale + z);
            }
            glEnd();
        }
    }

    // draw all children
    for (n = 0; n < nd->mNumChildren; ++n)
    {
        recursive_render(sc, nd->mChildren[n], scale, x, y, z);
    }

    glPopMatrix();
}

void Model::drawAiScene(const aiScene* scene, double factor, double x, double y, double z)
{
    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
    recursive_render(scene, scene->mRootNode, factor, x, y, z);
    glEndList();
}