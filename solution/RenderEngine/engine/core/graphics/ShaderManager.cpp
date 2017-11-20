#include "ShaderManager.h"
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/core/singletonsManager/SingletonsManager.h>

namespace sre
{

void ShaderManager::init()
{
	this->graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
}

void ShaderManager::release()
{
	this->graphicsWrapper->releaseShaders(this->vertShaders, this->fragShaders, this->programs);
}

uint32_t ShaderManager::loadGUIShader()
{
	std::string vertexContent;
	std::string fragmentContent;

	ShaderContentFactory contentFactory;
	contentFactory.createGUIShaderContent(vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadShader(const std::string &vertexContent, const std::string &fragmentContent)
{
	uint32_t vertShader = this->graphicsWrapper->loadVertexShader(vertexContent);
	uint32_t fragShader = this->graphicsWrapper->loadFragmentShader(fragmentContent);

	uint32_t program = this->graphicsWrapper->createProgram(vertShader, fragShader);

	this->vertShaders.push(vertShader);
	this->fragShaders.push(fragShader);
	this->programs.push(program);
	
	return program;
}

// passing values //
void ShaderManager::setInt(uint32_t program, const std::string &varName, int value)
{
	this->graphicsWrapper->setInt(program, varName, value);
}

void ShaderManager::setFloat(uint32_t program, const std::string &varName, float value)
{
	this->graphicsWrapper->setFloat(program, varName, value);
}

void ShaderManager::setVec3(uint32_t program, const std::string &varName, const float *value)
{
	this->graphicsWrapper->setVec3(program, varName, value);
}

void ShaderManager::setVec4(uint32_t program, const std::string &varName, const float *value)
{
	this->graphicsWrapper->setVec4(program, varName, value);
}

void ShaderManager::setMat4(uint32_t program, const std::string &varName, const float *value)
{
	this->graphicsWrapper->setMat4(program, varName, value);
}

void ShaderManager::enableShader(uint32_t program)
{
	this->graphicsWrapper->enableShader(program);
}

void ShaderManager::disableShader()
{
	this->graphicsWrapper->disableShader();
}

} // namespace
