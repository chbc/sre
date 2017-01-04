#include "ColorMaterialComponent.h"
#include "../Material.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

ColorMaterialComponent::ColorMaterialComponent(Material *material) : AMaterialComponent(material)
{
	this->color = glm::vec4{ 1.0f };
}

void ColorMaterialComponent::init()
{
}

/* ###
void ColorMaterial::apply(std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->renderManager->applyMaterial(this, receiveLight);
}
*/

void ColorMaterialComponent::setColor(const glm::vec4 &color)
{
	this->color = color;
}

glm::vec4 ColorMaterialComponent::getColor()
{
	return this->color;
}

} // namespace