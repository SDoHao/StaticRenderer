#include "scene_loader.h"
#include "sphere.h"
#include "triangle.h"
#include "disk.h"

// TinyXML2 — 单头文件库，将 tinyxml2.h / tinyxml2.cpp 加入项目即可
#include <tinyxml2.h>

namespace RENDERER
{

    /**
     * @brief 安全读取 XML 属性为 std::string，属性不存在时返回默认值
     *        解决 Attribute() 返回 nullptr 导致 std::string 构造崩溃的问题
     */
    static std::string safeAttribute(tinyxml2::XMLElement* elem,
                                      const char* attrName,
                                      const char* defaultValue)
    {
        const char* val = elem->Attribute(attrName);
        return val ? std::string(val) : std::string(defaultValue);
    }

    Vector3f SceneLoader::parseVector3f(const std::string& str)
    {
        Vector3f result(0.0f, 0.0f, 0.0f);
        float values[3] = {0.0f, 0.0f, 0.0f};
        int index = 0;

        std::string token;
        for (size_t i = 0; i <= str.size(); ++i)
        {
            char c = (i < str.size()) ? str[i] : ',';
            if (c == ',' || c == ' ')
            {
                if (!token.empty())
                {
                    if (index < 3)
                        values[index] = std::stof(token);
                    ++index;
                    token.clear();
                }
            }
            else
            {
                token += c;
            }
        }

        result.x = values[0];
        result.y = values[1];
        result.z = values[2];
        return result;
    }

    bool SceneLoader::parseCamera(Scene* scene, void* cameraElement, int viewWidth, int viewHeight)
    {
        tinyxml2::XMLElement* elem = static_cast<tinyxml2::XMLElement*>(cameraElement);

        Vector3f position = parseVector3f(safeAttribute(elem, "position", "0,0,0"));
        Vector3f target   = parseVector3f(safeAttribute(elem, "target",   "0,0,1"));
        Vector3f up       = parseVector3f(safeAttribute(elem, "up",       "0,1,0"));

        float fovDeg = elem->FloatAttribute("fov", 60.0f);
        float nearP  = elem->FloatAttribute("near", 0.1f);
        float farP   = elem->FloatAttribute("far", 1000.0f);

        Camera camera;
        camera.Initialize(position, target, up,
                          glm::radians(fovDeg), nearP, farP,
                          viewWidth, viewHeight);

        scene->setCamera(camera);
        return true;
    }

    bool SceneLoader::parseSceneObject(Scene* scene, void* objectElement)
    {
        tinyxml2::XMLElement* elem = static_cast<tinyxml2::XMLElement*>(objectElement);

        Vector3f position = parseVector3f(safeAttribute(elem, "position", "0,0,0"));
        Vector3f euler    = parseVector3f(safeAttribute(elem, "euler",    "0,0,0"));
        // XML 中 euler 使用角度，此处转为弧度传给 SceneObject
        euler = Vector3f(glm::radians(euler.x), glm::radians(euler.y), glm::radians(euler.z));
        float scale       = elem->FloatAttribute("scale", 1.0f);

        SceneObject* pSceneObject = scene->createSceneObject(position, euler, scale);
        if (!pSceneObject)
            return false;

        // 遍历子节点，创建 Primitive
        for (tinyxml2::XMLElement* child = elem->FirstChildElement();
             child != nullptr;
             child = child->NextSiblingElement())
        {
            const char* name = child->Name();
            if (!name) continue;

            if (strcmp(name, "sphere") == 0)
            {
                float radius = child->FloatAttribute("radius", 1.0f);
                pSceneObject->createPrimitive<Sphere>(radius);
            }
            else if (strcmp(name, "triangle") == 0)
            {
                Vector3f v0 = parseVector3f(safeAttribute(child, "v0", "0,0,0"));
                Vector3f v1 = parseVector3f(safeAttribute(child, "v1", "0,0,0"));
                Vector3f v2 = parseVector3f(safeAttribute(child, "v2", "0,0,0"));
                pSceneObject->createPrimitive<Triangle>(v0, v1, v2);
            }
            else if (strcmp(name, "disk") == 0)
            {
                float radius = child->FloatAttribute("radius", 1.0f);
                pSceneObject->createPrimitive<Disk>(radius);
            }
            else
            {
                std::cerr << "[SceneLoader] 未知 Primitive 类型: " << name << std::endl;
            }
        }

        return true;
    }

    bool SceneLoader::load(Scene* scene, const std::string& filePath, int viewWidth, int viewHeight)
    {
        if (!scene)
        {
            std::cerr << "[SceneLoader] Scene 指针为空" << std::endl;
            return false;
        }

        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError err = doc.LoadFile(filePath.c_str());
        if (err != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "[SceneLoader] 无法加载 XML 文件: " << filePath
                      << " (错误: " << doc.ErrorStr() << ")" << std::endl;
            return false;
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("scene");
        if (!root)
        {
            std::cerr << "[SceneLoader] 找不到 <scene> 根节点" << std::endl;
            return false;
        }

        // 解析 <camera>
        tinyxml2::XMLElement* cameraElem = root->FirstChildElement("camera");
        if (cameraElem)
        {
            if (!parseCamera(scene, cameraElem, viewWidth, viewHeight))
                return false;
        }
        else
        {
            std::cerr << "[SceneLoader] 警告: 未找到 <camera> 节点，使用默认摄像机" << std::endl;
        }

        // 解析所有 <sceneobject>
        for (tinyxml2::XMLElement* objElem = root->FirstChildElement("sceneobject");
             objElem != nullptr;
             objElem = objElem->NextSiblingElement("sceneobject"))
        {
            if (!parseSceneObject(scene, objElem))
            {
                std::cerr << "[SceneLoader] 解析 <sceneobject> 失败" << std::endl;
                return false;
            }
        }

        return true;
    }

} // namespace RENDERER
