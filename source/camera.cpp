#include "camera.h"
using namespace RENDERER;
void Camera::Initialize(const Vector3f& p, const Vector3f& target, const Vector3f& up,
        float fov,float n,float f,int W,int H){
    mPosition = p;

    // 求观察矩阵
    // Vector3f l = glm::normalize(target - p);
    // Vector3f r = glm::normalize(glm::cross(up,l));
    // Vector3f u = glm::cross(l,r);
    
    // Matrix44 viewMatrix = glm::transpose(
    //     Matrix44(
    //         r.x,r,y,r.z,0.0f,
    //         u.x,u,y,u.z,0.0f,
    //         l.x,l,y,l.z,0.0f,
    //         0.0f,0.0f,0.0f,1.0f)
    //     ) * makeTranslation(-p);

    // left-hand  左手坐标系
    Matrix44 viewMatrix = glm::lookAtLH(p,target,up);

    //求投影矩阵
    Matrix44 projectionMartix = glm::perspectiveFovLH_ZO(fov,(float)W,(float)H,n,f);

    //求视口矩阵
    Matrix44 viewportMatrix = glm::mat4(
        W / 2.0f,0.0f,0.0f,0.0f,
        0.0f,-H / 2.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        W / 2.0f,H / 2.0f,0.0f,1.0f
    );

    Matrix44 CombineMatrix = viewportMatrix * projectionMartix * viewMatrix;
    Matrix44 InvCombineMatrix = glm::inverse(CombineMatrix);
    mCombineMatrix = CombineMatrix;
    mInvCombineMatrix = InvCombineMatrix;
}

Ray Camera::getRay(int x,int y)const
{
    Ray ray;
    ray.o = mPosition;
    Vector4f p(x,y,0.0f,1.0f);
    Vector4f worldPos =  mInvCombineMatrix * p;

    worldPos /= worldPos.w;

    ray.d = glm::normalize(Vector3f(worldPos) - mPosition);

    return ray;
}