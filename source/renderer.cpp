#include <renderer.h>

namespace RENDERER {
    Renderer::Renderer(int w, int h):mViewWidth(w),mViewHeight(h){
        mCurrentPixelIndex = 0;

        mScene  = new Scene();
        Camera mTesCamera;
        mTesCamera.Initialize(
            Vector3f(0.0f,0.0f,0.0f),
            Vector3f(0.0f,0.0f,1.0f),
            Vector3f(0.0f,1.0f,0.0f),
            glm::radians(60.0f),
            0.1f,
            1000.0f,
            w,h
        );
        mScene->setCamera(mTesCamera);

        //给场景添加物体
        SceneObject * mTestSceneObject = mScene->createSceneObject(Vector3f(0,0,5),Vector3f(0,0,0),2.0f);
        mTestSceneObject->createPrimitive<Triangle>(Vector3f(-1,-1,0),Vector3f(1,-1,0),Vector3f(1,1,0));
        mTestSceneObject->createPrimitive<Triangle>(Vector3f(-1,-1,0),Vector3f(1,1,0),Vector3f(-1,1,0));

        SceneObject * mSphere = mScene->createSceneObject(Vector3f(0,0,2),Vector3f(0,0,0),2.0f);
        mTestSceneObject->createPrimitive<Sphere>(0.5f);
    }
    
    Renderer::~Renderer()
    {
        if(mScene)
            delete mScene;
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
        Ray ray = mScene->getCamera().getRay(x,y);
        Intersection isect;
        Color color(0,0,0);
        if(mScene->intersect(ray,isect))
        {
            color = isect.normal * 0.5f + 0.5f;
        }
        return color;
    }

    // Color  Renderer::renderSubPixel(int x,int y)
    // {


    // }

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