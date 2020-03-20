#ifndef _GUI_RENDERER_H_
#define _GUI_RENDERER_H_

#include <list>
#include "memory_aliases.h"

namespace sre
{

class GUIImageComponent;
class AGraphicsWrapper;
class ShaderManager;
class MatrixManager;

class GUIRenderer
{
protected:
    std::list<GUIImageComponent *> guiComponents;
    std::list<GUIImageComponent *> dynamicGUIComponents;
    uint32_t shaderProgram;

    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

private:
    class Shader *shader;

private:
    GUIRenderer(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void loadShader();
    void addGUIComponent(GUIImageComponent *guiComponent);
    void addDynamicGUIComponent(GUIImageComponent *guiComponent);
    void render(MatrixManager *matrixManager);
    void setup(GUIImageComponent *guiComponent);

    void removeDestroyedEntities();

friend class RenderManager;
};

} // namespace

#endif