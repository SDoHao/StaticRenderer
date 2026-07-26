#ifndef RENDERER_H
#define RENDERER_H
#include<MiniFB.h>
#include<iostream>

namespace RENDERER {
    class Renderer
    {
    public:
        Renderer(){}
        virtual ~Renderer(){}
        void run();

    };

}
#endif