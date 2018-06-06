#ifndef _SHADOW_RENDERER_SHADER_SETUP_H_
#define _SHADOW_RENDERER_SHADER_SETUP_H_

#include "BaseRendererShaderSetup.h"

namespace sre
{

class ShadowRendererShaderSetup : public BaseRendererShaderSetup
{
protected:
    class LightManager *lightManager;

    ShadowRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(Shader *shader) override;
    void setupShaderValues(Shader *shader) override;

friend class Renderer;
};

} // namespace

#endif
