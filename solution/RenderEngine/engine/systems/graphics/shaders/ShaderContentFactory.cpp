#include "ShaderContentFactory.h"
#include <engine/utils/FileUtils.h>
#include "ShaderFiles.h"

namespace sre
{

void ShaderContentFactory::createColorContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string vertexContentHeader;
	std::string fragmentContentHeader;
	this->loadColorContentHeader(vertexContentHeader, fragmentContentHeader);

	std::string vertexContentImpl;
	std::string fragmentContentImpl;
	this->loadColorContentImplementation(vertexContentImpl, fragmentContentImpl);

	outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
	outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
}

void ShaderContentFactory::createDiffuseContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string vertexContentHeader;
	std::string fragmentContentHeader;
	this->loadDiffuseContentHeader(vertexContentHeader, fragmentContentHeader);

	std::string vertexContentImpl;
	std::string fragmentContentImpl;
	this->loadDiffuseContentImplementation(vertexContentImpl, fragmentContentImpl);

	outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
	outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
}

void ShaderContentFactory::createNormalMapContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string vertexContentHeader;
	std::string fragmentContentHeader;
	this->loadNormalMapContentHeader(vertexContentHeader, fragmentContentHeader);

	std::string vertexContentImpl;
	std::string fragmentContentImpl;
	this->loadNormalMapContentImplementation(vertexContentImpl, fragmentContentImpl);

	outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
	outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
}

// Load methods
void ShaderContentFactory::loadColorContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string lightsVertex;
	std::string mainVertex;
	std::string lightsFragment;
	std::string mainFragment;

	FileUtils::loadFile(ShaderFiles::LIGHTS_H_V, lightsVertex);
	FileUtils::loadFile(ShaderFiles::MAIN_H_V, mainVertex);
	FileUtils::loadFile(ShaderFiles::LIGHTS_H_F, lightsFragment);
	FileUtils::loadFile(ShaderFiles::MAIN_H_F, mainFragment);

	outVertexContent = lightsVertex + mainVertex;
	outFragmentContent = lightsFragment + mainFragment;
}

void ShaderContentFactory::loadColorContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string lightsVertex;
	std::string mainVertex;
	std::string lightsFragment;
	std::string mainFragment;

	FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_V, lightsVertex);
	FileUtils::loadFile(ShaderFiles::MAIN_IMPL_V, mainVertex);
	FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_F, lightsFragment);
	FileUtils::loadFile(ShaderFiles::MAIN_IMPL_F, mainFragment);

	outVertexContent = lightsVertex + mainVertex;
	outFragmentContent = lightsFragment + mainFragment;
}

void ShaderContentFactory::loadDiffuseContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string diffuseVertex;
	std::string diffuseFragment;

	FileUtils::loadFile(ShaderFiles::DIFFUSE_H_V, diffuseVertex);
	FileUtils::loadFile(ShaderFiles::DIFFUSE_H_F, diffuseFragment);

	this->loadColorContentHeader(outVertexContent, outFragmentContent);

	outVertexContent = diffuseVertex + outVertexContent;
	outFragmentContent = diffuseFragment + outFragmentContent;
}

void ShaderContentFactory::loadDiffuseContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string diffuseVertex;
	std::string diffuseFragment;

	FileUtils::loadFile(ShaderFiles::DIFFUSE_IMPL_V, diffuseVertex);
	FileUtils::loadFile(ShaderFiles::DIFFUSE_IMPL_F, diffuseFragment);

	this->loadColorContentImplementation(outVertexContent, outFragmentContent);

	outVertexContent = diffuseVertex + outVertexContent;
	outFragmentContent = diffuseFragment + outFragmentContent;

	this->uncommentCode(outVertexContent, "// [DIFFUSE] ");
	this->uncommentCode(outFragmentContent, "// [DIFFUSE] ");
}

void ShaderContentFactory::loadNormalMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string normalVertex;
	std::string normalFragment;

	FileUtils::loadFile(ShaderFiles::NORMAL_H_V, normalVertex);
	FileUtils::loadFile(ShaderFiles::NORMAL_H_F, normalFragment);

	this->loadDiffuseContentHeader(outVertexContent, outFragmentContent);

	outVertexContent = normalVertex + outVertexContent;
	outFragmentContent = normalFragment + outFragmentContent;
}

void ShaderContentFactory::loadNormalMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string normalVertex;
	std::string normalFragment;

	FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_V, normalVertex);
	FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_F, normalFragment);

	this->loadDiffuseContentImplementation(outVertexContent, outFragmentContent);

	outVertexContent = normalVertex + outVertexContent;
	outFragmentContent = normalFragment + outFragmentContent;

	this->uncommentCode(outVertexContent, "// [NORMAL] ");
	this->uncommentCode(outFragmentContent, "// [NORMAL] ");
}

void ShaderContentFactory::replaceCode(std::string &outShaderContent, const char *code)
{
	std::size_t beginCodePosition = outShaderContent.find("// ###");
	std::size_t size = outShaderContent.size() - beginCodePosition;
	if (beginCodePosition != std::string::npos)
	{
		outShaderContent = outShaderContent.replace
		(
			beginCodePosition, size,
			code
		);
	}
	else
		throw "[ShaderContentFactory] - Didn't find code mark!";
}

void ShaderContentFactory::uncommentCode(std::string &outShaderContent, const std::string &mark)
{
	std::size_t position = outShaderContent.find(mark);
	if (position != std::string::npos)
		outShaderContent = outShaderContent.erase(position, mark.size());
	else
		throw "[ShaderContentFactory] - Didn't find code mark!";
}

} // namespace
