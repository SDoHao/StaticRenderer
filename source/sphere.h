#ifndef SPHERE_H
#define SPHERE_H
#include "common.h"
#include "ray.h"

namespace RENDERER{
    struct Intersection
    {
        //世界坐标系下
        Vector3f position;          //交点位置
        Vector3f normal;            //交点法线
        float t;                    //射线参数t值，即交点到射线原点的距离
    };


    class Sphere
    {
    public:
        Sphere(const Vector3f& center,float radius);
        bool intersect(Ray ray, Intersection& isect) const;
        ~Sphere();
    private:
        float mRadius = 1;
        Matrix44 mObject2World;     // 对象空间到世界空间的变换矩阵
        Matrix44 mWorld2Object;     // 世界空间到对象空间的变换矩阵
    };
    inline Sphere::~Sphere() {}};

#endif