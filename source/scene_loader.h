#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include "scene.h"
#include "camera.h"
#include <string>

namespace RENDERER
{
    /**
     * @brief 从 XML 文件加载场景配置
     *
     * XML 格式示例:
     * <scene>
     *     <camera position="0,0,0" target="0,0,1" up="0,1,0" fov="60" near="0.1" far="1000"/>
     *     <sceneobject position="0,0,5" euler="0,0,0" scale="2.0">
     *         <triangle v0="-1,-1,0" v1="1,-1,0" v2="1,1,0"/>
     *         <sphere radius="0.5"/>
     *         <disk radius="1.0"/>
     *     </sceneobject>
     * </scene>
     */
    class SceneLoader
    {
    public:
        /**
         * @brief 从 XML 文件加载场景到已有的 Scene 对象
         * @param scene  目标场景指针
         * @param filePath  XML 文件路径
         * @param viewWidth  视口宽度（传给 Camera::Initialize）
         * @param viewHeight 视口高度（传给 Camera::Initialize）
         * @return true 加载成功, false 加载失败
         */
        static bool load(Scene* scene, const std::string& filePath, int viewWidth, int viewHeight);

    private:
        // 解析 "x,y,z" 格式的字符串为 Vector3f
        static Vector3f parseVector3f(const std::string& str);

        // 解析 <camera> 节点
        static bool parseCamera(Scene* scene, void* cameraElement, int viewWidth, int viewHeight);

        // 解析 <sceneobject> 节点及其子节点
        static bool parseSceneObject(Scene* scene, void* objectElement);
    };

} // namespace RENDERER

#endif // SCENE_LOADER_H
