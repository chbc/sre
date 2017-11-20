#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <string>
#include <engine/core/singletonsManager/ASingleton.h>
#include "shaders/ShaderContentFactory.h"
#include <stack>
#include <bitset>

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to deal with GLSL API
*/
class ShaderManager : ASingleton
{
protected:
	void init() override;
    void release() override;

private:
	std::stack<uint32_t> vertShaders;
	std::stack<uint32_t> fragShaders;
	std::stack<uint32_t> programs;

	AGraphicsWrapper *graphicsWrapper;

	// main load function
	template <size_t SIZE> uint32_t loadShader(const std::bitset<SIZE> &componentsBitset)
	{
		std::string vertexContent;
		std::string fragmentContent;

		ShaderContentFactory contentFactory;
		contentFactory.createShaderContent(componentsBitset, vertexContent, fragmentContent);

		return this->loadShader(vertexContent, fragmentContent);
	}
	uint32_t loadGUIShader();
	uint32_t loadShader(const std::string &vertexContent, const std::string &fragmentContent);

	// passing values //
	void setInt(uint32_t program, const std::string &varName, int value);
	void setFloat(uint32_t program, const std::string &varName, float value);
	void setVec3(uint32_t program, const std::string &varName, const float *value);
	void setVec4(uint32_t program, const std::string &varName, const float *value);
	void setMat4(uint32_t program, const std::string &varName, const float *value);

	void enableShader(uint32_t program);
	void disableShader();

friend class RenderManager;
friend class LightManager;
friend class SingletonsManager;

friend class Renderer;
friend class GUIRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
};

} // namespace

#endif
