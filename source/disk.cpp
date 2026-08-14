
#include "disk.h"

namespace RENDERER
{
    Disk::Disk(SceneObject* pSceneObject,float radius)
        :Primitive(pSceneObject),mRadius(radius)
    {
    }
    
    bool Disk::intersect(Ray ray, Intersection& isect) const
    {
        // ray转换成局部坐标系
        Ray r = m_pSceneObject->getWorldToObject() * ray;
        if(fabs(r.d.z) < 1e-6f)
            return false;

        float t = -r.o.z / r.d.z;

        if(t < r.mint || t > r.maxt)
            return false;

        Vector3f p = r.o + t * r.d; // 交点

        //判断交点是否再圆盘内
        if(glm::dot(p,p) > mRadius * mRadius)
            return false;

        isect.position = Vector3f(m_pSceneObject->getObjectToWorld() * Vector4f(p,1.0f));
        isect.normal = glm::normalize(Vector3f(m_pSceneObject->getObjectToWorld() * Vector4f(0,0,1,0)));
        isect.t = t;

        return true;
    }
}