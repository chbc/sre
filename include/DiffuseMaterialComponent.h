#ifndef _DIFFUSE_MATERIAL_COMPONENT_H_
#define _DIFFUSE_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include "memory_aliases.h"

namespace sre
{

class Texture;

class SRE_API DiffuseMaterialComponent : public AMaterialComponent
{
private:
    Texture *texture;

public:
	DiffuseMaterialComponent(Material *material, const std::string &fileName);

	void loadTexture(const std::string &fileName);
	uint32_t getTextureID(uint32_t index = 0);
};

} // namespace
#endif
