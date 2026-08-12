#ifndef SPHERE_H
#define SPHERE_H
#include "primitive.h"

namespace RENDERER{

    class Sphere : public Primitive
    {
    public:
        Sphere(const Vector3f& center,float radius);
        virtual bool intersect(Ray ray, Intersection& isect) const override;
        ~Sphere();
    private:
        float mRadius = 1;
        Matrix44 mObject2World;     // 对象空间到世界空间的变换矩阵
        Matrix44 mWorld2Object;     // 世界空间到对象空间的变换矩阵
    };
    inline Sphere::~Sphere() {}};

#endif