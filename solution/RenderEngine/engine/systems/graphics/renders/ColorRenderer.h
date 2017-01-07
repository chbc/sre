#ifndef _COLOR_RENDERER_H_
#define _COLOR_RENDERER_H_

#include <engine/utils/memory_aliases.h>
#include <glm/vec3.hpp>
#include <vector>

namespace sre
{

class MeshComponent;
class MatrixManager;
class AGraphicsWrapper;
class MatrixManager;
class ShaderManager;
class AGraphicsWrapper;
class LightManager;

class ColorRenderer
{
private:
	std::vector<MeshComponent *> meshes;
	UPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

	uint32_t shaderProgram;
	int vertexAttribLocation;
	int normalAttribLocation;

public:
	~ColorRenderer();

private:
	ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void addMesh(MeshComponent *mesh);
	void createVBO(MeshComponent *mesh);	// ###
	uint32_t loadShader(const std::string &vertFile, const std::string &fragFile);
	void render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition);

friend class RenderManager;
};

} // namespace

#endif
