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

    struct Intersection
    {
        //世界坐标系下
        Vector3f position;          //交点位置
        Vector3f normal;            //交点法线
        float t;                    //射线参数t值，即交点到射线原点的距离
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