#include "scene.h"

namespace RENDERER{
    SceneObject *Scene::createSceneObject(const Vector3f& position,const Vector3f& euler,float scale)
    {
        SceneObject * pSceneObject = new SceneObject(position,euler,scale);
        mSceneObjects.push_back(pSceneObject);
        return pSceneObject;
    }

    SceneObject *Scene::intersect(Ray ray, Intersection &isect) const
    {
        SceneObject * pHitObject = nullptr;
        for ( SceneObject * const pSceneObject : mSceneObjects) // const 修饰的是指针变量本身
        {
            if(pSceneObject->intersect(ray,isect))
            {
                ray.maxt = isect.t;
                pHitObject = pSceneObject;
            }
        }

        return pHitObject;
    }

    Scene::~Scene()
    {
        for (SceneObject* pSceneObject : mSceneObjects)
        {
            delete pSceneObject;
        }
    }
}
