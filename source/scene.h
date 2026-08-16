#ifndef SCENE_H
#define SCENE_H
#include "scene_object.h"
#include "camera.h"

namespace RENDERER
{
    class Scene
    {
    public:
        void setCamera(const Camera& camera){mCamera = camera;}
        const Camera& getCamera()const {return mCamera;}
        SceneObject *  createSceneObject(const Vector3f& position,const Vector3f& euler,float scale);
        SceneObject * intersect(Ray ray,Intersection& isect)const;
        ~Scene();
    private:
        Camera mCamera;
        std::vector<SceneObject*> mSceneObjects;
    };



}
#endif