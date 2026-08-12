#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "ray.h"

namespace RENDERER
{
    class Primitive
    {
    public:
        virtual ~Primitive(){}
        virtual  bool intersect(Ray ray, Intersection &isect)const = 0;
    };
} 

#endif