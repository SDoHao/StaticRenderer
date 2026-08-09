#ifndef RAY_H
#define RAY_H
#include "common.h"

namespace RENDERER{
    struct Ray
    {
        RENDERER::Vector3f o;
        RENDERER::Vector3f d;
        float mint = 0.0f;
        float maxt = FLT_MAX;
    };

    inline Ray operator*(const Matrix44& m,const Ray& r)
    {
        Ray result;
        result.o = Vector3f(m * Vector4f(r.o,1.0f));    //坐标向量需要平移
        result.d = Vector3f(m * Vector4f(r.d,0.0f));    //方向向量不需要平移
        result.mint = r.mint;
        result.maxt = r.maxt;
        return result;
    }
}


#endif