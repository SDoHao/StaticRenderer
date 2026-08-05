#ifndef RAY_H
#define RAY_H
#include "common.h"

struct Ray
{
    RENDERER::Vector3f o;
    RENDERER::Vector3f d;
    float mint = 0.0f;
    float maxt = FLT_MAX;
};


#endif