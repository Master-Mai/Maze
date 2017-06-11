#pragma comment(lib, "legacy_stdio_definitions.lib")
#ifndef SNOW_PARTICLE_H
#define SNOW_PARTICLE_H
#include "Particle.h"
#include <GL\GLAUX.H>

class SnowParticle {
private:
    /** 创建一个粒子类对象 */
    CParticle Snow;

    /** 用来设置粒子的属性值 */
    float x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec;
    int r, g, b;
    GLuint g_texture = 0;
public:
    SnowParticle() {}
    //载入一个.bmp格式的贴图纹理
    int LoadGLTextures(GLuint& unTexture, const char* chFileName)
    {
        AUX_RGBImageRec *TextureImage;                    //保存贴图数据的指针
        TextureImage = auxDIBImageLoad(chFileName); //载入贴图数据

        glGenTextures(1, &unTexture);                    // 创建一个纹理，unTexture

        glBindTexture(GL_TEXTURE_2D, unTexture);        //绑定纹理，然后对该纹理区添加纹理数据

                                                        //设置纹理的信息，
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //设置滤波为线性滤波
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //线性滤波

        if (TextureImage)                //释放资源
        {
            if (TextureImage->data)
            {
                free(TextureImage->data);
            }
            free(TextureImage);
        }

        return 1;
    }

    /** 初始化雪花粒子 */
    bool InitSnow()
    {
        for (int i = 0; i < Snow.GetNumOfParticle(); ++i)
        {
            ///初始化颜色（白色）
            r = 255;
            g = 255;
            b = 255;
            Snow.SetColor(i, r, g, b);

            ///初始化坐标
            x = 0.1f * (rand() % 50) - 2.5f;
            y = 2 + 0.1f * (rand() % 2);
            if ((int)x % 2 == 0)
                z = rand() % 6;
            else
                x = -rand() % 3;
            Snow.SetPosition(i, x, y, z);

            ///初始化速度
            vx = 0.00001 * (rand() % 100);
            vy = 0.0000002 * (rand() % 28000);
            vz = 0;
            Snow.SetVelocity(i, vx, vy, vz);

            ///初始化加速度
            ax = 0;
            ay = 0.000005f;
            az = 0;
            Snow.SetAcceleration(i, ax, ay, az);

            ///初始化生命周期
            lifetime = 100;
            Snow.SetLifeTime(i, lifetime);

            ///消失速度
            dec = 0.005 * (rand() % 50);
            Snow.SetDec(i, dec);

            ///初始化大小
            Snow.SetSize(i, 0.01f);
        }
        return true;
    }

    /** 更新粒子 */
    void UpdateSnow()
    {
        /** 更新位置 */
        x += (vx * 5);
        y -= vy;

        /** 更新速度 */
        vy += ay;

        /** 更新生存时间 */
        lifetime -= dec;

        if (x > 3)
            x = -2;

        /** 如果粒子消失或生命结束 */
        if (y <= -1 || lifetime <= 0)
        {
            /** 初始化位置 */
            x = 0.1f * (rand() % 50) - 2.5f;
            y = 2 + 0.1f * (rand() % 2);
            if ((int)x % 2 == 0)
                z = rand() % 6;
            else
                z = -rand() % 3;

            /** 初始化速度 */
            vx = (float)(0.00001 * (rand() % 100));
            vy = (float)(0.0000002 * (rand() % 28000));
            vz = 0;

            /** 初始化加速度 */
            ax = 0;
            ay = 0.000005f;
            az = 0;
            lifetime = 100;
            dec = 0.005*(rand() % 50);
        }
    }

    /** 绘制粒子 */
    void DrawParticle()
    {
        /** 绑定纹理 */
        //glBindTexture(GL_TEXTURE_2D, g_texture);

        for (int i = 0; i<Snow.GetNumOfParticle(); ++i)
        {
            /** 获得粒子的所有属性 */
            Snow.GetAll(i, r, g, b, x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec);
            glLoadIdentity();
            glTranslatef(0.0f, 0.0f, -6.0f);
            glColor4ub(r, g, b, 255);
            //glNormal3f(0.0f, 0.0f, 1.0f);   /**< 定义法线方向 */
                                            /** 画出粒子 */
            glPointSize(5.0f);
            glBegin(GL_POINTS);
            /*glTexCoord2f(0.0f, 0.0f); glVertex3f(x - size, y - size, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x - size, y + size, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y - size, z);*/
            glVertex3f(x, y, z);
            glEnd();

            /** 更新粒子属性 */
            UpdateSnow();
            Snow.SetAll(i, r, g, b, x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec);
        }
        //glutPostRedisplay();//发送渲染请求
    }

    /////////////////////////////////////////////////////////////////
    /** 初始化 */
    void init(void)
    {
        ///** 用户自定义的初始化过程 */
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);    /**< 设置混合因子获得半透明效果 */
        //glEnable(GL_BLEND);                  /**< 启用混和 */

        //LoadGLTextures(g_texture, "resources/images/snowball.bmp");

        /** 创建xx个粒子 */
        Snow.Create(500);

        /** 初始化粒子 */
        InitSnow();
    }
};

#endif  // SNOW_PARTICLE_H
