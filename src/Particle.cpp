#include "Particle.h"

/** ���캯�� */
CParticle::CParticle()
{
    data = NULL;
    numparticle = 0;

}

/** �������� */
CParticle::~CParticle()
{
    delete[]data;
    data = NULL;
}

/** ����һ������num��Ԫ�ص��������� */
int CParticle::Create(long num)
{
    /** ɾ���������� */
    if (data)
        delete[]data;

    /** �������� */
    if (data = new Particle[num])
    {
        memset(data, 0, sizeof(Particle)*numparticle);
        numparticle = num;

        /** �������Ӹ��� */
        return numparticle;
    }
    return 0;
}


/** ���úͻ�ȡ��ɫColor�ĺ���ʵ�� */
int CParticle::SetColor(GLint r, GLint g, GLint b)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].r = r;
        data[index].g = g;
        data[index].b = b;
    }
    return true;
}

int CParticle::SetColor(GLint index, GLint r, GLint g, GLint b)
{
    if (index >= 0 && index<numparticle)
    {
        data[index].r = r;
        data[index].g = g;
        data[index].b = b;
        return true;
    }
    return false;
}

int CParticle::GetColor(GLint index, GLint &r, GLint &g, GLint &b)
{
    if (index >= 0 && index<numparticle)
    {
        r = data[index].r;
        g = data[index].g;
        b = data[index].b;
        return true;
    }
    return false;
}

/** ���úͻ�ȡλ��Position�ĺ���ʵ�� */
int CParticle::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].x = x;
        data[index].y = y;
        data[index].z = z;
    }
    return true;
}

int CParticle::SetPosition(GLint index, GLfloat x, GLfloat y, GLfloat z)
{
    if (index >= 0 && index<numparticle)
    {
        data[index].x = x;
        data[index].y = y;
        data[index].z = z;
        return true;
    }
    return false;
}

int CParticle::GetPosition(GLint index, GLfloat &x, GLfloat &y, GLfloat &z)
{
    if (index >= 0 && index<numparticle)
    {
        x = data[index].x;
        y = data[index].y;
        z = data[index].z;
        return true;
    }
    return false;
}
/** ���úͻ�ȡ���ٶ�Acceleration�ĺ���ʵ�� */
int CParticle::SetAcceleration(GLfloat ax, GLfloat ay, GLfloat az)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].ax = ax;
        data[index].ay = ay;
        data[index].az = az;
    }
    return true;
}

int CParticle::SetAcceleration(GLint index, GLfloat ax, GLfloat ay, GLfloat az)
{
    if (index >= 0 && index<numparticle)
    {
        data[index].ax = ax;
        data[index].ay = ay;
        data[index].az = az;
        return true;
    }
    return false;
}


int CParticle::GetAcceletation(GLint index, GLfloat &ax, GLfloat &ay, GLfloat &az)
{
    if (index >= 0 && index<numparticle)
    {
        ax = data[index].ax;
        ay = data[index].ay;
        az = data[index].az;
        return true;
    }
    return false;
}



/** Velocity������ʵ�� */
int CParticle::SetVelocity(GLfloat vx, GLfloat vy, GLfloat vz)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].vx = vx;
        data[index].vy = vy;
        data[index].vz = vz;
    }
    return true;
}

int CParticle::SetVelocity(GLint index, GLfloat vx, GLfloat vy, GLfloat vz)
{
    if (index >= 0 && index<numparticle)
    {
        data[index].vx = vx;
        data[index].vy = vy;
        data[index].vz = vz;
        return true;
    }
    return false;
}

int CParticle::GetVelocity(GLint index, GLfloat &vx, GLfloat &vy, GLfloat &vz)
{
    if (index >= 0 && index<numparticle)
    {
        vx = data[index].vx;
        vy = data[index].vy;
        vz = data[index].vz;
        return true;
    }
    return false;
}


/** Size������ʵ�� */
int CParticle::SetSize(GLfloat size)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].size = size;
    }
    return true;
}

int CParticle::SetSize(GLint index, GLfloat size)
{
    if (index >= 0 && index<numparticle)
    {
        data[index].size = size;
        return true;
    }
    return false;
}

int CParticle::GetSize(GLint index, GLfloat &size)
{
    if (index >= 0 && index < numparticle)
    {
        size = data[index].size;
        return true;
    }
    return false;
}

/** ��ʧ�ٶ�Dec���� */
int CParticle::SetDec(GLfloat dec)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].dec = dec;
    }
    return true;
}

int CParticle::SetDec(GLint index, GLfloat dec)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].dec = dec;
        return true;
    }
    return false;
}

int CParticle::GetDec(GLint index, GLfloat &dec)
{
    if (index >= 0 && index < numparticle)
    {
        dec = data[index].dec;
        return true;
    }
    return false;
}

/** �������ӵ�lifetime ���� */
int CParticle::SetLifeTime(GLfloat lifetime)
{
    for (int index = 0; index<numparticle; ++index)
    {
        data[index].lifetime = lifetime;
    }
    return true;
}

int CParticle::SetLifeTime(GLint index, GLfloat lifetime)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].lifetime = lifetime;
        return true;
    }
    return false;
}

/** ������ӵ�lifetime���� */
int CParticle::GetLifeTime(GLint index, GLfloat &lifetime)
{
    if (index >= 0 && index < numparticle)
    {
        lifetime = data[index].lifetime;
        return true;
    }
    return false;
}

/** ��ȡ���ӵ��������� */
int CParticle::GetAll(int index, GLint &r, GLint &g, GLint &b,         /**< ���ӵ���ɫ */
    GLfloat &x, GLfloat &y, GLfloat &z,     /**< λ�� */
    GLfloat &vx, GLfloat &vy, GLfloat &vz,  /**< �ٶ� */
    GLfloat &ax, GLfloat &ay, GLfloat &az,  /**< ���ٶ� */
    GLfloat &size,                            /**< ��С */
    GLfloat &lifetime,                        /**< ����ʱ�� */
    GLfloat &dec                          /**< ��ʧ�ٶ� */
    )
{
    if (index >= 0 && index<numparticle)
    {
        r = data[index].r;
        g = data[index].g;
        b = data[index].b;
        x = data[index].x;
        y = data[index].y;
        z = data[index].z;
        vx = data[index].vx;
        vy = data[index].vy;
        vz = data[index].vz;
        ax = data[index].ax;
        ay = data[index].ay;
        az = data[index].az;
        lifetime = data[index].lifetime;
        size = data[index].size;
        dec = data[index].dec;
        return true;
    }
    return false;
}

/** �������ӵ��������� */
int CParticle::SetAll(int index, GLint r, GLint g, GLint b,        /**< ���ӵ���ɫ */
    GLfloat x, GLfloat y, GLfloat z,        /**< λ�� */
    GLfloat vx, GLfloat vy, GLfloat vz, /**< �ٶ� */
    GLfloat ax, GLfloat ay, GLfloat az, /**< ���ٶ� */
    GLfloat size,                     /**< ��С */
    GLfloat lifetime,                 /**< ����ʱ�� */
    GLfloat dec                           /**< ��ʧ�ٶ� */
    )
{
    if (index >= 0 && index<numparticle)
    {
        data[index].r = r;
        data[index].g = g;
        data[index].b = b;
        data[index].x = x;
        data[index].y = y;
        data[index].z = z;
        data[index].vx = vx;
        data[index].vy = vy;
        data[index].vz = vz;
        data[index].ax = ax;
        data[index].ay = ay;
        data[index].az = az;
        data[index].lifetime = lifetime;
        data[index].size = size;
        data[index].dec = dec;
        return true;
    }
    return false;
}