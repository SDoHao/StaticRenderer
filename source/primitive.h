#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "ray.h"

namespace RENDERER
{
    class SceneObject;

    class Primitive
    {
    public:
        Primitive(SceneObject * pSceneObject) : m_pSceneObject(pSceneObject){}
        virtual ~Primitive(){}
        virtual  bool intersect(Ray ray, Intersection &isect)const = 0;
    protected:
        SceneObject* m_pSceneObject = nullptr;
    };
} 

#endif