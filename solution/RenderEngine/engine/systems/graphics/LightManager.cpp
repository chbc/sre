#include "LightManager.h"

#include <engine/entities/Entity.h>
#include "ShaderManager.h"

namespace sre
{

LightManager::LightManager()
{
	this->ambientLightColor = glm::vec3(0.3f, 0.3f, 0.3f);
}

LightManager::~LightManager()
{
	/* ####
	std::vector<LightNode *>::iterator itLight = this->lightNodes.begin();
	while(itLight != this->lightNodes.end())
	{
		delete (*itLight);
		itLight++;
	}
	this->lightNodes.clear();
	*/
}

void LightManager::setAmbientLightColor(const glm::vec3 &ambientLightColor)
{
	this->ambientLightColor = ambientLightColor;
}

DirectionalLightComponent *LightManager::addDirectionalLight(Entity *entity)
{
	DirectionalLightComponent *newLight = entity->addComponent<DirectionalLightComponent>();
	this->directionalLights.push_back(newLight);

	return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
	PointLightComponent *newLight = entity->addComponent<PointLightComponent>();
	this->pointLights.push_back(newLight);

	return newLight;
}

void LightManager::setupLights(ShaderManager *shaderManager, uint32_t program)
{
	this->setupDirectionalLights(shaderManager, program);
	this->setupPointLights(shaderManager, program);

	shaderManager->setVec3(program, "lights.ambientLightColor", &this->ambientLightColor[0]);
}

void LightManager::setupDirectionalLights(ShaderManager *shaderManager, uint32_t program)
{
    char variable[100];

    DirectionalLightComponent *light = nullptr;
    int count = this->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->directionalLights[i];
		glm::vec3 direction = light->getDirection();
		glm::vec3 color = light->getColor();

        sprintf_s(variable, "lights.directionalLights[%d].direction", i);
        shaderManager->setVec3(program, variable, &direction[0]);

        sprintf_s(variable, "lights.directionalLights[%d].color", i);
        shaderManager->setVec3(program, variable, &color[0]);
    }

    shaderManager->setInt(program, "lights.directionalLightsCount", count);
}

void LightManager::setupPointLights(ShaderManager *shaderManager, uint32_t program)
{
    char variable[100];

    PointLightComponent *light = nullptr;
    int count = this->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->pointLights[i];
		glm::vec3 position = light->getTransform()->getPosition();
		glm::vec3 color = light->getColor();

        sprintf_s(variable, "lights.pointLights[%d].position", i);
        shaderManager->setVec3(program, variable, &position[0]);

        sprintf_s(variable, "lights.pointLights[%d].color", i);
        shaderManager->setVec3(program, variable, &color[0]);
    }

    shaderManager->setInt(program, "lights.pointLightsCount", count);
}

} // namespace
