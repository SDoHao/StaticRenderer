#include "sphere.h"

namespace RENDERER
{
    Sphere::Sphere(SceneObject* pSceneObject, float radius)
        : Primitive(pSceneObject),mRadius(radius)
    {

    }

    bool RENDERER::Sphere::intersect(Ray ray, Intersection &isect) const
    {
        // ray转换成球体局部空间
        Ray r = m_pSceneObject->getWorldToObject() * ray;
        float A = glm::dot(r.d,r.d);
        float B = 2.0f * glm::dot(r.d,r.o);
        float C = glm::dot(r.o,r.o) - mRadius * mRadius;
        float delta = B * B - 4.0f * A * C;

        if(delta < 0.0f)return false;
        float sqrtDelta = sqrtf(delta);
        float t1 = (-B - sqrtDelta) / (2.0f * A);
        float t2 = (-B + sqrtDelta) / (2.0f * A);

        // t1一定小于t2
        if(t2 < r.mint || t1 > r.maxt)return false;
        float t = t1;
        if(t < r.mint){
            if(t2 > r.maxt)return false;
            t = t2;
        }

        Vector3f p = r.o + t * r.d;
        Vector3f n = glm::normalize(p);

        isect.position = Vector3f(m_pSceneObject->getObjectToWorld() * Vector4f(p,1.0f));
        isect.normal = glm::normalize(Vector3f(m_pSceneObject->getObjectToWorld() * Vector4f(n,0.0f)));
        isect.t = t;
        
        return true;
    }

}