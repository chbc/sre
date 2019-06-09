#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

#include <stdint.h>

// ### TRANSFORMAR OS COMPONENTES EM SINGLETONS
// ### RENOMEAR PRA REFERENCIAR OS MESHES
namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class Shader;

class ColorRendererComponent
{
protected:
    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

protected:
    ColorRendererComponent(ShaderManager *shaderManager, class AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(Shader *shader);
    virtual void setupShaderValues(class MeshComponent *mesh, Shader *shader);
    virtual void preDraw();
    virtual void postDraw();

friend class Renderer;
};

} // namespace

#endif
