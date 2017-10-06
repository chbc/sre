#include "Renderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/core/graphics/MatrixManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/graphics/LightManager.h>

namespace sre
{

Renderer::Renderer(Material *material, const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
{
	this->shaderManager = shaderManager;
	this->graphicsWrapper = graphicsWrapper;

	for (int i = 0; i <= EMaterialMap::SIZE; i++)
	{
		if (material->componentsBitset[i])
		{
			switch (i)
			{
				case EMaterialMap::COLOR:
					this->addComponent<ColorRendererComponent>(this->shaderManager, this->graphicsWrapper);
					break;
				case EMaterialMap::DIFFUSE:
					this->addComponent<DiffuseRendererComponent>(this->shaderManager, this->graphicsWrapper);
					break;
				case EMaterialMap::NORMAL:
					this->addComponent<NormalRendererComponent>(this->shaderManager, this->graphicsWrapper);
					break;
				case EMaterialMap::SPECULAR:
					this->addComponent<SpecularRendererComponent>(this->shaderManager, this->graphicsWrapper);
					break;
				case EMaterialMap::AMBIENT_OCCLUSION:
					this->addComponent<AORendererComponent>(this->shaderManager, this->graphicsWrapper);
					break;
				default: break;
			}
		}
	}
}

Renderer::~Renderer()
{
	for (MeshComponent *item : this->meshes)
		this->graphicsWrapper->deleteBuffers(item);
}

void Renderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadShader(this->componentsBitset);
}

void Renderer::addMesh(MeshComponent *mesh)
{
	this->meshes.push_back(mesh);
	this->graphicsWrapper->createVAO(mesh);
	this->graphicsWrapper->createEBO(mesh);
}

void Renderer::removeMesh(MeshComponent *mesh)
{
	this->meshes.remove(mesh);
}

void Renderer::render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition)
{
	// Shader setup
	this->shaderManager->enableShader(this->shaderProgram);

	glm::mat4 viewMatrix = matrixManager->getViewMatrix();
	glm::mat4 projectionMatrix = matrixManager->getProjectionMatrix();

	// ### obter a localização das variáveis do shader
	this->shaderManager->setMat4(this->shaderProgram, "viewMatrix", &viewMatrix[0][0]);
	this->shaderManager->setMat4(this->shaderProgram, "projectionMatrix", &projectionMatrix[0][0]);
	this->shaderManager->setVec3(this->shaderProgram, "cameraPosition", &cameraPosition[0]);

	lightManager->setupLights(this->shaderManager.get(), this->shaderProgram);

	for (MeshComponent *mesh : this->meshes)
	{
		// Matrix setup
		TransformComponent *transform = mesh->getTransform();
		glm::mat4 modelMatrix = transform->getMatrix();
		this->shaderManager->setMat4(this->shaderProgram, "modelMatrix", &modelMatrix[0][0]);

		this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
		for (const UPTR<ColorRendererComponent> &item : this->components)
		{
			item->setupShaderVariables(mesh, this->shaderProgram);
			item->preDraw();
		}

		this->graphicsWrapper->drawElement(mesh->objectData->indices.size());

		for (const UPTR<ColorRendererComponent> &item : this->components)
			item->postDraw();
	}

	this->shaderManager->disableShader();
}

bool Renderer::contains(MeshComponent *mesh)
{
	bool result = false;

	for (MeshComponent *item : this->meshes)
	{
		if (item == mesh)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool Renderer::fitsWithMesh(MeshComponent *mesh)
{
	return (this->componentsBitset == mesh->getMaterial()->componentsBitset);
}

} // namespace
