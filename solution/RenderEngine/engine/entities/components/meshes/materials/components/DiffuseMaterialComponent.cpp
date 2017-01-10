#include "DiffuseMaterialComponent.h"
#include <iostream>
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

DiffuseMaterialComponent::DiffuseMaterialComponent(Material *material, const std::string &fileName) 
	: AMaterialComponent(material)
{
	this->loadTexture(fileName);
}

void DiffuseMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *texture = RenderManager::getInstance()->loadTexture(fileName);
	this->textures.emplace_back(texture);
}

unsigned int DiffuseMaterialComponent::getTextureID(uint32_t index)
{
	if (index >= this->textures.size())
		throw "[DiffuseMaterialComponent] texture index out of range!";

	return this->textures[index]->getId();
}

} // namespace