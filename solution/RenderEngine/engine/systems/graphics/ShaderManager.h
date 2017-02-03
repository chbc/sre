#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <string>
#include <engine/utils/memory_aliases.h>
#include <engine/utils/EShaderVariable.h>
#include <stack>

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to deal with GLSL API
*/
class ShaderManager
{
public:
	~ShaderManager();

public:
	std::stack<uint32_t> vertShaders;
	std::stack<uint32_t> fragShaders;
	std::stack<uint32_t> programs;

	SPTR<AGraphicsWrapper> graphicsWrapper;

	ShaderManager(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	// main load function
	unsigned int loadColorShader();
	unsigned int loadDiffuseShader();

	// passing values //
	void setInt(uint32_t program, const std::string &varName, int value);
	void setFloat(uint32_t program, const std::string &varName, float value);
	void setVec3(uint32_t program, const std::string &varName, const float *value);
	void setVec4(uint32_t program, const std::string &varName, const float *value);
	void setMat4(uint32_t program, const std::string &varName, const float *value);

	int getAttribLocation(uint32_t program, EShaderVariable::Type shaderVariable);

	void enableShader(uint32_t program);
	void disableShader();

friend class RenderManager;
friend class LightManager;
friend class ColorRenderer;	// ###
};

} // namespace

#endif
