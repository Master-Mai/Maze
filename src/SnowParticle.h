#pragma comment(lib, "legacy_stdio_definitions.lib")
#ifndef SNOW_PARTICLE_H
#define SNOW_PARTICLE_H
#include "Particle.h"
#include <GL\GLAUX.H>

class SnowParticle {
private:
    /** ����һ����������� */
    CParticle Snow;

    /** �����������ӵ�����ֵ */
    float x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec;
    int r, g, b;
    GLuint g_texture = 0;
public:
    SnowParticle() {}
    //����һ��.bmp��ʽ����ͼ����
    int LoadGLTextures(GLuint& unTexture, const char* chFileName)
    {
        AUX_RGBImageRec *TextureImage;                    //������ͼ���ݵ�ָ��
        TextureImage = auxDIBImageLoad(chFileName); //������ͼ����

        glGenTextures(1, &unTexture);                    // ����һ������unTexture

        glBindTexture(GL_TEXTURE_2D, unTexture);        //������Ȼ��Ը������������������

                                                        //�����������Ϣ��
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�����˲�Ϊ�����˲�
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //�����˲�

        if (TextureImage)                //�ͷ���Դ
        {
            if (TextureImage->data)
            {
                free(TextureImage->data);
            }
            free(TextureImage);
        }

        return 1;
    }

    /** ��ʼ��ѩ������ */
    bool InitSnow()
    {
        for (int i = 0; i < Snow.GetNumOfParticle(); ++i)
        {
            ///��ʼ����ɫ����ɫ��
            r = 255;
            g = 255;
            b = 255;
            Snow.SetColor(i, r, g, b);

            ///��ʼ������
            x = 0.1f * (rand() % 50) - 2.5f;
            y = 2 + 0.1f * (rand() % 2);
            if ((int)x % 2 == 0)
                z = rand() % 6;
            else
                x = -rand() % 3;
            Snow.SetPosition(i, x, y, z);

            ///��ʼ���ٶ�
            vx = 0.00001 * (rand() % 100);
            vy = 0.0000002 * (rand() % 28000);
            vz = 0;
            Snow.SetVelocity(i, vx, vy, vz);

            ///��ʼ�����ٶ�
            ax = 0;
            ay = 0.000005f;
            az = 0;
            Snow.SetAcceleration(i, ax, ay, az);

            ///��ʼ����������
            lifetime = 100;
            Snow.SetLifeTime(i, lifetime);

            ///��ʧ�ٶ�
            dec = 0.005 * (rand() % 50);
            Snow.SetDec(i, dec);

            ///��ʼ����С
            Snow.SetSize(i, 0.01f);
        }
        return true;
    }

    /** �������� */
    void UpdateSnow()
    {
        /** ����λ�� */
        x += (vx * 5);
        y -= vy;

        /** �����ٶ� */
        vy += ay;

        /** ��������ʱ�� */
        lifetime -= dec;

        if (x > 3)
            x = -2;

        /** ���������ʧ���������� */
        if (y <= -1 || lifetime <= 0)
        {
            /** ��ʼ��λ�� */
            x = 0.1f * (rand() % 50) - 2.5f;
            y = 2 + 0.1f * (rand() % 2);
            if ((int)x % 2 == 0)
                z = rand() % 6;
            else
                z = -rand() % 3;

            /** ��ʼ���ٶ� */
            vx = (float)(0.00001 * (rand() % 100));
            vy = (float)(0.0000002 * (rand() % 28000));
            vz = 0;

            /** ��ʼ�����ٶ� */
            ax = 0;
            ay = 0.000005f;
            az = 0;
            lifetime = 100;
            dec = 0.005*(rand() % 50);
        }
    }

    /** �������� */
    void DrawParticle()
    {
        /** ������ */
        //glBindTexture(GL_TEXTURE_2D, g_texture);

        for (int i = 0; i<Snow.GetNumOfParticle(); ++i)
        {
            /** ������ӵ��������� */
            Snow.GetAll(i, r, g, b, x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec);
            glLoadIdentity();
            glTranslatef(0.0f, 0.0f, -6.0f);
            glColor4ub(r, g, b, 255);
            //glNormal3f(0.0f, 0.0f, 1.0f);   /**< ���巨�߷��� */
                                            /** �������� */
            glPointSize(5.0f);
            glBegin(GL_POINTS);
            /*glTexCoord2f(0.0f, 0.0f); glVertex3f(x - size, y - size, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x - size, y + size, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y - size, z);*/
            glVertex3f(x, y, z);
            glEnd();

            /** ������������ */
            UpdateSnow();
            Snow.SetAll(i, r, g, b, x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec);
        }
        //glutPostRedisplay();//������Ⱦ����
    }

    /////////////////////////////////////////////////////////////////
    /** ��ʼ�� */
    void init(void)
    {
        ///** �û��Զ���ĳ�ʼ������ */
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);    /**< ���û�����ӻ�ð�͸��Ч�� */
        //glEnable(GL_BLEND);                  /**< ���û�� */

        //LoadGLTextures(g_texture, "resources/images/snowball.bmp");

        /** ����xx������ */
        Snow.Create(500);

        /** ��ʼ������ */
        InitSnow();
    }
};

#endif  // SNOW_PARTICLE_H
