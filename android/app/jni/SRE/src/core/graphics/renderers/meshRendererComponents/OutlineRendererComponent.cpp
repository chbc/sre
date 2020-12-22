#include "OutlineRendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

OutlineRendererComponent::OutlineRendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void OutlineRendererComponent::onSceneLoaded(class Shader* shader)
{
    // XXX this->shaderManager->setupUniformLocation(shader, ShaderVariables::OUTLINE_COLOR);
}

void OutlineRendererComponent::setupShaderValues(MeshComponent* mesh, Shader* shader)
{
}

void OutlineRendererComponent::preDraw()
{
    this->graphicsWrapper->enableVertexPositions();
}

void OutlineRendererComponent::postDraw()
{
    this->graphicsWrapper->disableVertexPositions();
}

} // namespace
