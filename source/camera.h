#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"

using namespace RENDERER;

class Camera
{
public:
    void Initialize(const Vector3f& p, const Vector3f& target, const Vector3f& up,
        float fov,float n,float f,int W,int H);
    Ray getRay(int x,int y)const;
private:
    Vector3f mPosition;
    Matrix44 mCombineMatrix;
    Matrix44 mInvCombineMatrix;

};

#endif