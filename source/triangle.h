#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "primitive.h"
#include "scene_object.h"

namespace RENDERER
{
    class Triangle : public Primitive
    {
    public:
        Triangle(SceneObject* pSceneObject,const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);
        virtual bool intersect(Ray ray, Intersection& isect) const override;
    private:
        // 世界坐标系下的三角形顶点位置和法线
        Vector3f mVertices[3];      // 三角形的三个顶点
        Vector3f mNormal;           // 三角形的发现
    };

}

#endif