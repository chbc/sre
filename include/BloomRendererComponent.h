#ifndef _BLOOM_RENDERER_COMPONENT_H_
#define _BLOOM_RENDERER_COMPONENT_H_

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class BloomRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct GUIMeshData> meshData;

	class Shader* blurShader;
	class Shader* combineShader;
	
	uint32_t initialPassTextureId;
	uint32_t brightnessTextureId;
	uint32_t blurTextureIds[2];

	uint32_t initialPassFBO;
	uint32_t brightnessFBOs[2];

	uint32_t blurInteractionsCount = 10;

private:
	BloomRendererComponent(class PostProcessingComponent* component);

protected:
	void onPreRender();
	void onPostRender();

friend class PostProcessingRenderer;
};

}  // namespace

#endif
