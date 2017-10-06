#ifndef _GUI_RENDERER_H_
#define _GUI_RENDERER_H_

#include <list>
#include <engine/utils/memory_aliases.h>

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

	SPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

private:
	GUIRenderer(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader();
	void addGUIComponent(GUIImageComponent *guiComponent);
	void addDynamicGUIComponent(GUIImageComponent *guiComponent);
	void removeGUIComponent(GUIImageComponent *guiComponent);
	void render(MatrixManager *matrixManager);
	void setup(GUIImageComponent *guiComponent);

friend class RenderManager;
};

} // namespace

#endif
