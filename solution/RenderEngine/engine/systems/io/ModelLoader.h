#ifndef _MODEL_LOADER_H_
#define _MODEL_LOADER_H_

#include <string>

struct aiNode;
struct aiScene;
struct aiMesh;

namespace sre
{

class Entity;
class MeshComponent;

class ModelLoader
{
private:
	std::string directory;

	ModelLoader() {}

	Entity *load(const std::string &fileName);
	Entity *processNode(aiNode *node, const aiScene *scene);
	void processMesh(aiMesh *inputMesh, const aiScene *scene, Entity *entity);
	void processMaterials(aiMesh *inputMesh, const aiScene *scene, MeshComponent *entityMesh);

friend class SceneManager;
};

} // namespace

#endif
