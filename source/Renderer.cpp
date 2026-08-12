#include <renderer.h>

namespace RENDERER {
    Renderer::Renderer(int w, int h):mViewWidth(w),mViewHeight(h){
        mCurrentPixelIndex = 0;
        mCamera.Initialize(
            Vector3f(0.0f,0.0f,0.0f),
            Vector3f(0.0f,0.0f,1.0f),
            Vector3f(0.0f,1.0f,0.0f),
            glm::radians(60.0f),
            0.1f,
            1000.0f,
            w,h
        );

        auto * mSphere = new Sphere(Vector3f(1,1,4),1.0f);
        auto * mDisk = new Disk(Vector3f(0,-2,5),Vector3f(glm::radians(90.0f),0,0),1.0f);
        auto * mTriangle = new Triangle(Vector3f(-1,0,0),Vector3f(0,1,0),Vector3f(1,0,0),
            makeWorldTransform(Vector3f(0,0,5),Vector3f(0,0,0),2.0f));

        mPrimitives.push_back(mSphere);
        mPrimitives.push_back(mDisk);
        mPrimitives.push_back(mTriangle);
    }

    void  Renderer::run()
    {
        struct mfb_window * window = mfb_open_ex("Render", mViewWidth, mViewHeight, MFB_WF_RESIZABLE);
        if (window == NULL)
            return;

        mbuffer = (uint32_t *)malloc(mViewWidth * mViewHeight * 4);

        int numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> renderThreads(numThreads);
        for(int i = 0;i < numThreads;i++)
        {
            renderThreads[i] = std::thread(&Renderer::runRenderThread,this); 
            renderThreads[i].detach();
        }

        mfb_update_state state;
        do {
            state = mfb_update_ex(window, mbuffer, mViewWidth, mViewHeight);

            if (state != MFB_STATE_OK)
                break;

        } while(mfb_wait_sync(window));

        free(mbuffer);
        mbuffer = NULL;
        window = NULL;
    }

    Color  Renderer::renderPixel(int x,int y)
    {
        Ray ray = mCamera.getRay(x,y);
        // RENDERER::Vector3f d = ray.d;
        // Color color(d * 0.5f + 0.5f);
        // return Color(1.0f,0.3f,0.7825f)0;
        // Color color;
        // color.r = (float)x / mViewWidth;
        // color.g = (float)y / mViewHeight;
        // color.b = 0.0f;
        // Color color(1.1f,0.89f,0.0f);
        // Color color((float)x / mViewWidth, (float)y / mViewHeight, 0.0f);
        // 绘制每个像素等待1秒，模拟耗时渲染
        Intersection isect;
        for (auto &primitive : mPrimitives)
        {
            if (primitive ->intersect(ray,isect))
            {  
                // 光源方向，模拟从右上方照过来
                Vector3f lightDir = glm::normalize(Vector3f(0.0f,1.0f,-1.5f));

                // 朗伯漫反射：法线 · 光照方向，clamp到0~1，不能负数
                float ndotl = glm::dot(isect.normal, lightDir);
                float diffuse = glm::clamp(ndotl, 0.0f, 1.0f);

                return Color(diffuse, diffuse, 0);
            }
        }
        

        return Color(0,0,0);

        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // return color;
    }

   void Renderer::runRenderSingleThread()
   {
        for(int y = 0;y < mViewHeight;y++)
        {
            for(int x = 0;x < mViewWidth;x++)
            {
                Color color = renderPixel(x,y);
                uint32_t r = glm::clamp((uint32_t)std::round(color.r * 255.f),0u,255u);
                uint32_t g = glm::clamp((uint32_t)std::round(color.g * 255.f),0u,255u);
                uint32_t b = glm::clamp((uint32_t)std::round(color.b * 255.f),0u,255u);
                mbuffer[y * mViewWidth + x] = (r << 16) | (g << 8) | (b);
            }
        }
    }

    void Renderer::runRenderThread()
    {
        //读取当前屏幕的下一个像素
        while(true)
        {
                int pixelIndex = mCurrentPixelIndex.fetch_add(1);
                if(pixelIndex >= mViewWidth * mViewHeight)
                    break;

                int x = pixelIndex % mViewWidth;
                int y = pixelIndex / mViewWidth;

                Color color = renderPixel(x,y);
                uint32_t r = glm::clamp((uint32_t)std::round(color.r * 255.f),0u,255u);
                uint32_t g = glm::clamp((uint32_t)std::round(color.g * 255.f),0u,255u);
                uint32_t b = glm::clamp((uint32_t)std::round(color.b * 255.f),0u,255u);
                mbuffer[y * mViewWidth + x] = (r << 16) | (g << 8) | (b);
        }
    }
}