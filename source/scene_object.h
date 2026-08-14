#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
#include "ray.h"
#include "primitive.h"
#include "vector"

namespace RENDERER
{
    class SceneObject
    {
    public:
        SceneObject(const Vector3f& position,const Vector3f& euler,float scale)
        {
            mObject2World = makeWorldTransform(position,euler,scale);
            mWorld2Object = glm::inverse(mObject2World);
        }
        virtual ~SceneObject();
        bool intersect(Ray ray,Intersection& isect)const;
        void addPrimitive(Primitive * primitive){mPrimitives.push_back(primitive);}
        const Matrix44& getObjectToWorld()const {return mObject2World;}
        const Matrix44& getWorldToObject()const {return mWorld2Object;}
        
    private: 
        Matrix44 mObject2World;     // 对象空间到世界空间的变换矩阵
        Matrix44 mWorld2Object;     // 世界空间到对象空间的变换矩阵
        std::vector<Primitive*> mPrimitives;
    };
   
}

#endif