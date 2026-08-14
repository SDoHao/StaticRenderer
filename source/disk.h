#ifndef DISK_H
#define DISK_H
#include "primitive.h"
#include "scene_object.h"

namespace RENDERER{
    class Disk : public Primitive
    {
    public:
        Disk(SceneObject* pSceneObject,float radius);
        virtual bool intersect(Ray ray, Intersection& isect) const override;
    private:
        float mRadius = 1;
    };
}

#endif