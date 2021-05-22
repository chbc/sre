#ifndef _SPECULAR_MATERIAL_COMPONENT_H_
#define _SPECULAR_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <string>

namespace sre
{

class SRE_API SpecularMaterialComponent : public AMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
	class Texture* texture;
	
public:
	SpecularMaterialComponent(Material *material, const std::string &fileName);

	uint32_t getTextureID(uint32_t index = 0) const;
};

} // namespace

#endif
