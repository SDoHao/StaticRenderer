#ifndef COMMON_H
#define COMMON_H
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>

namespace RENDERER {
    using Vector2f = glm::vec2;
    using Vector3f = glm::vec3;
    using Vector4f = glm::vec4;

    using Vector2i = glm::ivec2;
    using Vector3i = glm::ivec3;
    using Vector4i = glm::ivec4;

    using Matrix33 = glm::mat3;
    using Matrix44 = glm::mat4;

    const float PI = glm::pi<float>(); //3.14159265358979323846f;

    inline void dumpVector(const Vector3f& v3)
    {
        std::cout << "Vector3f(" << v3.x << "," << v3.y << "," << v3.z << ")"<<std::endl;
    }
    
    //构造平移方法
    inline Matrix44 makeTranslation(const Vector3f &t)
    {
        return Matrix44(
            1.0f,0.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,0.0f,
            0.0f,0.0f,1.0f,0.0f,
            t.x,t.y,t.z,1.0f
        );
    }
    // Vector3f p(1.0f,2.0f,3.0f);
    // Vector3f t(4.0f,5.0f,6.0f);
    // Matrix44 T = makeTranslation(t);
    // Vector3f p2 = T * Vector4f(p,1.0);//四维向量向三维向量有一个隐式转换。

    /// 缩放矩阵
    inline Matrix44 makeScale(const Vector3f &s)
    {
        return Matrix44(
            s.x, 0.0f, 0.0f, 0.0f,
            0.0f, s.y, 0.0f, 0.0f,
            0.0f, 0.0f, s.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    //等比例缩放
    inline Matrix44 makeScale(float s)
    {
        return Matrix44(
            s, 0.0f, 0.0f, 0.0f,
            0.0f, s, 0.0f, 0.0f,
            0.0f, 0.0f, s, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    /// 绕 X 轴旋转（angle：弧度）
    inline Matrix44 makeRotateX(float angleRad)
    {
        float c = cosf(angleRad);
        float s = sinf(angleRad);
        return Matrix44(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, c,   s,   0.0f,
            0.0f, -s,  c,   0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    /// 绕 Y 轴旋转（angle：弧度）
    inline Matrix44 makeRotateY(float angleRad)
    {
        float c = cosf(angleRad);
        float s = sinf(angleRad);
        return Matrix44(
            c,   0.0f, -s,  0.0f,
            0.0f,1.0f, 0.0f,0.0f,
            s,   0.0f, c,   0.0f,
            0.0f,0.0f, 0.0f,1.0f
        );
    }

    // 绕Z轴旋转
    inline Matrix44 makeRotateZ(float angleRad)
    {
        float c = cosf(angleRad);
        float s = sinf(angleRad);
        return Matrix44(
            c,   s,   0.0f, 0.0f,
            -s,  c,   0.0f, 0.0f,
            0.0f,0.0f,1.0f, 0.0f,
            0.0f,0.0f,0.0f, 1.0f
        );
    }

    
    /**
    * @brief 欧拉角生成3种旋转矩阵
    * @param euler 欧拉角 (ax, ay, az) 弧度 = 角度 / 180° * PI  or glm::redians(角度)
    * 矩阵组合: Rz * Ry * Rx
    * 执行顺序：先绕X → 再绕Y → 最后绕Z
    **/
    inline Matrix44 makeEulerRotate(const Vector3f& euler)
    {
        float ax = euler.x;
        float ay = euler.y;
        float az = euler.z;

        float cx = cosf(ax), sx = sinf(ax);
        float cy = cosf(ay), sy = sinf(ay);
        float cz = cosf(az), sz = sinf(az);

        // Rz * Ry * Rx 展开结果
        float m00 = cz * cy;
        float m01 = cz * sy * sx + sz * cx;
        float m02 = -cz * sy * cx + sz * sx;

        float m10 = -sz * cy;
        float m11 = -sz * sy * sx + cz * cx;
        float m12 = sz * sy * cx + cz * sx;

        float m20 = sy;
        float m21 = -cy * sx;
        float m22 = cy * cx;

        // glm::mat4 构造顺序：col0,col1,col2,col3
        return Matrix44(
            m00, m10, m20, 0.0f,
            m01, m11, m21, 0.0f,
            m02, m12, m22, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }
    // inline Matrix44 makeEulerRotateDirect(const Vector3f& euler)
    // {
    //     float ax = euler.x;
    //     float ay = euler.y;
    //     float az = euler.z;

    //     // 预计算所有sin/cos
    //     float cx = cosf(ax), sx = sinf(ax);
    //     float cy = cosf(ay), sy = sinf(ay);
    //     float cz = cosf(az), sz = sinf(az);

    //     // Rx 绕X
    //     Matrix44 Rx(
    //         1,  0,   0,   0,
    //         0,  cx,  sx,  0,
    //         0, -sx,  cx,  0,
    //         0,  0,   0,   1
    //     );
    //     // Ry 绕Y
    //     Matrix44 Ry(
    //         cy,  0, -sy, 0,
    //         0,   1,  0,  0,
    //         sy,  0,  cy, 0,
    //         0,   0,  0,  1
    //     );
    //     // Rz 绕Z
    //     Matrix44 Rz(
    //         cz, sz, 0, 0,
    //         -sz, cz, 0, 0,
    //         0,  0,  1, 0,
    //         0,  0,  0, 1
    //     );

    //     //rz * ry * rx 顺序是先绕x 再绕y 最后绕z
    //     return Rz * Ry * Rx;
    // }
    inline Matrix44 makeWorldTransform(const Vector3f& position,const Vector3f& rotation,float s)
    {
        Matrix44 T = makeTranslation(position);
        Matrix44 R = makeEulerRotate(rotation);
        Matrix44 S = makeScale(s);
        return T * R * S;
    }

    //构造的新坐标系到世界坐标系的旋转矩阵
    inline Matrix33 makeCoordinateSystem(const Vector3f w)
    {
        Vector3f u(1.0f,0.0f,0.0f);
        if(glm::dot(w,u) > 0.99f)
        {
            u = Vector3f(0.0f,1.0f,0.0f);
        }
        Vector3f v = glm::cross(w,u);
        u = glm::cross(v,w);
        return Matrix33(glm::normalize(u),glm::normalize(v),w);
    }
}

#endif