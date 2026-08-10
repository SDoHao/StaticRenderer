
#include "disk.h"

namespace RENDERER
{
    Disk::Disk(const Vector3f& center,const Vector3f& euler,float radius)
        :mRadius(radius)
    {
        mObject2World = makeWorldTransform(center,euler,1.0f);
        mWorld2Object = glm::inverse(mObject2World);
    }
    
    bool Disk::intersect(Ray ray, Intersection& isect) const
    {
        // ray转换成局部坐标系
        Ray r = mWorld2Object * ray;
        if(fabs(r.d.z) < 1e-6f)
            return false;

        float t = -r.o.z / r.d.z;

        if(t < r.mint || t > r.maxt)
            return false;

        Vector3f p = r.o + t * r.d; // 交点

        //判断交点是否再圆盘内
        if(glm::dot(p,p) > mRadius * mRadius)
            return false;

        isect.position = Vector3f(mObject2World * Vector4f(p,1.0f));
        isect.normal = glm::normalize(Vector3f(mObject2World * Vector4f(0,0,1,0)));
        isect.t = t;

        return true;
    }
}