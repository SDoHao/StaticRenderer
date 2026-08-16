#ifndef RENDERER_H
#define RENDERER_H
#include "common.h"
#include "scene.h"
#include "scene_loader.h"
#include <MiniFB.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

namespace RENDERER {
    class Renderer
    {
    public:
        Renderer(){}
        Renderer(int w, int h, const std::string& sceneFile = "scene.xml");
        virtual ~Renderer();
        void run();
    private:
        Color renderPixel(int x,int y);
        // Color renderSubPixel(int x,int y);
        void runRenderSingleThread();
        void runRenderThread();
        int mViewWidth = 800;
        int mViewHeight = 600;
        uint32_t * mbuffer = nullptr;
        std::atomic<int> mCurrentPixelIndex = 0;

        Scene * mScene = nullptr;
    };

}
#endif
