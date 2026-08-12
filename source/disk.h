#ifndef DISK_H
#define DISK_H
#include "primitive.h"
namespace RENDERER{
    class Disk : public Primitive
    {
    public:
        Disk(const Vector3f& center,const Vector3f& euler,float radius);
        virtual bool intersect(Ray ray, Intersection& isect) const override;
    private:
        float mRadius = 1;
        Matrix44 mObject2World;     // 对象空间到世界空间的变换矩阵
        Matrix44 mWorld2Object;     // 世界空间到对象空间的变换矩阵
    };
}
#endif