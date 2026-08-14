#ifndef SPHERE_H
#define SPHERE_H
#include "primitive.h"
#include "scene_object.h"

namespace RENDERER{

    class Sphere : public Primitive
    {
    public:
        Sphere(SceneObject* pSceneObject,float radius);
        virtual bool intersect(Ray ray, Intersection& isect) const override;
        ~Sphere();
    private:
        float mRadius = 1;
    };
    inline Sphere::~Sphere() {}};

#endif