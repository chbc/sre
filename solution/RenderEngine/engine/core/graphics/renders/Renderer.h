#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <engine/entities/components/AComponentsHolder.h>
#include "ColorRendererComponent.h"
#include "DiffuseRendererComponent.h"
#include "NormalRendererComponent.h"
#include "SpecularRendererComponent.h"
#include "AORendererComponent.h"
#include "LightRendererComponent.h"
#include <glm/vec3.hpp>
#include <list>

namespace sre
{

class MeshComponent;
class Material;
class MatrixManager;
class AGraphicsWrapper;
class ShaderManager;

class Renderer : public AComponentsHolder<ColorRendererComponent>
{
private:
    std::list<MeshComponent *> meshes;
    class Shader *shader;

    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

    int viewMatrixLocation;
    int projectionMaxtrixLocation;
    int cameraPositionLocation;
    int modelMatrixLocation;

public:
    virtual ~Renderer();

private:
    Renderer(Material *material, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void loadShader();
    void onSceneLoaded();

    template <typename T, typename... TArgs>
    T *addComponent(TArgs&&... mArgs)
    {
        T *newComponent{ nullptr };

        if (!AComponentsHolder<ColorRendererComponent>::hasComponent<T>())
        {
            newComponent = new T{ std::forward<TArgs>(mArgs)... };
            AComponentsHolder<ColorRendererComponent>::addComponent(newComponent);
        }
        else
            throw "Can't add duplicate component!";

        return newComponent;
    }
    
    void addMesh(MeshComponent *mesh);

    void render(class Shader *shader);
    void render(MatrixManager *matrixManager, const glm::vec3 &cameraPosition);

    bool contains(MeshComponent *mesh);
    bool fitsWithMesh(MeshComponent *mesh);
    inline bool isEmpty() { return this->meshes.empty(); }

    void removeDestroyedEntities();

    friend class RenderManager;
};

} // namespace

#endif
