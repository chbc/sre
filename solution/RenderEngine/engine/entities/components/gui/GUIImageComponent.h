#ifndef _GUI_IMAGE_COMPONENT_H_
#define _GUI_IMAGE_COMPONENT_H_

#include "../AEntityComponent.h"
#include <engine/utils/memory_aliases.h>
#include <engine/systems/graphics/meshData/MeshData.h>

namespace sre
{

class Texture;

class GUIImageComponent : public AEntityComponent
{
private:
	Texture *texture;

	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;

	glm::vec2 uiPosition;

protected:
	UPTR<MeshData<GUIVertexData>> meshData;

private:
	GUIImageComponent(Entity *entity, const std::string &fileName);

protected:
	GUIImageComponent(Entity *entity);

public:
	void setUIPosition(const glm::vec2 &position);
	glm::vec2 getUIPosition();
	virtual uint32_t getTextureId();

friend class Entity;
friend class OpenGLAPI;
friend class GUIRenderer;
};

} // namespace

#endif
