#include "HDRRendererComponent.h"

#include "SingletonsManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "PrimitiveMeshFactory.h"
#include "PostProcessingComponent.h"

namespace sre
{

HDRRendererComponent::HDRRendererComponent(PostProcessingComponent* component)
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
	this->shaderManager = singletonsManager->get<ShaderManager>();

	this->shader = this->shaderManager->loadPostProcessingShader(component);
	this->shaderManager->setupUniformLocation(shader, ShaderVariables::SCREEN_TEXTURE);

	MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
	uint32_t width = static_cast<uint32_t>(multimediaManager->getScreenWidth());
	uint32_t height = static_cast<uint32_t>(multimediaManager->getScreenHeight());

	glm::vec2 pixelSize(width, height);
	glm::vec2 screenBasedSize = SingletonsManager::getInstance()->resolve<MultimediaManager>()->getNormalizedSize(pixelSize);

	GUIMeshData* quad = PrimitiveMeshFactory().createPlaneBottomUp(screenBasedSize);
	this->meshData = UPTR<GUIMeshData>{ quad };

	this->graphicsWrapper->createGUIVAO(quad, 0, false);
	this->graphicsWrapper->createGUIEBO(quad, 0, false);

	TextureManager* textureManager = singletonsManager->resolve<TextureManager>();
	Texture* texture = textureManager->createEmptyFloatingPointTexture(width, height);
	this->textureId = texture->getId();

	this->fbo = this->graphicsWrapper->generateColorFrameBuffer(
		std::vector<uint32_t>{this->textureId}, width, height
	);
}

void HDRRendererComponent::onPreRender()
{
	this->graphicsWrapper->bindFrameBuffer(this->fbo);
}

void HDRRendererComponent::onPostRender()
{
	this->graphicsWrapper->bindFrameBuffer(0);
	this->graphicsWrapper->clearColorBuffer();
	this->shaderManager->enableShader(this->shader);
	this->shaderManager->setInt(this->shader, ShaderVariables::SCREEN_TEXTURE, EMaterialMap::GUI);

	this->graphicsWrapper->bindVAO(this->meshData->vao, this->meshData->vbo);
	this->graphicsWrapper->enablePostProcessingSettings();
	this->graphicsWrapper->activateGUITexture(this->textureId);

	this->graphicsWrapper->drawElement(this->meshData->indices.size());

	this->graphicsWrapper->disablePostProcessingSettings();
	this->shaderManager->disableShader();
}

} // namespace
