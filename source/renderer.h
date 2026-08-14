#ifndef RENDERER_H
#define RENDERER_H
#include "common.h"
#include "camera.h"
#include "sphere.h"
#include "disk.h"
#include "triangle.h"
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
        Renderer(int w, int h);
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
        Camera mCamera;

        SceneObject* mTestSceneObject = nullptr;
    };

}
#endif