#ifndef _POST_PROCESSING_RENDERER_H_
#define _POST_PROCESSING_RENDERER_H_

#include "memory_aliases.h"
#include <stdint.h>

namespace sre
{

class PostProcessingRenderer
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	
	class Shader* shader;
	UPTR<class GUIMeshData> meshData;
	uint32_t textureId;
	uint32_t fbo;


private:
	PostProcessingRenderer();

	void onSceneLoaded();
	void bindFrameBuffer();
	void render();

friend class RenderManager;
};

} // namespace

#endif
