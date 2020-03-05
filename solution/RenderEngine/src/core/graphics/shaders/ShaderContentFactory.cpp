#include "ShaderContentFactory.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "ShaderConstants.h"
#include "PostProcessingComponent.h"

namespace sre
{

void ShaderContentFactory::createGUIShaderContent(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::GUI_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::GUI_F, outFragmentContent);
}

void ShaderContentFactory::createPointLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent, std::string &outGeometryContent)
{
    FileUtils::loadFile(ShaderFiles::POINT_SHADOW_DEPTH_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::POINT_SHADOW_DEPTH_F, outFragmentContent);
    FileUtils::loadFile(ShaderFiles::POINT_SHADOW_DEPTH_G, outGeometryContent);
}

void ShaderContentFactory::createDirectionalLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::DIRECTIONAL_SHADOW_DEPTH_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::DIRECTIONAL_SHADOW_DEPTH_F, outFragmentContent);
}

void ShaderContentFactory::createPostProcessingShaderContent(PostProcessingComponent* component, std::string& outVertexContent, std::string& outFragmentContent)
{
	std::string mainFragmentContentHeader;
	std::string mainFragmentContentImpl;

	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_V, outVertexContent);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_H_F, mainFragmentContentHeader);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_IMPL_F, mainFragmentContentImpl);

	std::string effectContent;

	for (const UPTR<PostProcessingEffect>& item : component->effects)
	{
		switch (item->type)
		{
			case PPE::ANTI_ALIASING: break;
			case PPE::BLOOM: break;
			case PPE::DEPTH_OF_FIELD: break;
			case PPE::GRAYSCALE: break;
			case PPE::INVERSE:
				FileUtils::loadFile(ShaderFiles::POST_PROCESSING_INVERSE_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->uncommentCode(mainFragmentContentImpl, "// [INVERSE] ");
				break;

			default: break;
		}
	}

	outFragmentContent = "#version 400\n" + mainFragmentContentHeader + mainFragmentContentImpl;
}

// Load methods
void ShaderContentFactory::loadColorContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::MAIN_H_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::MAIN_H_F, outFragmentContent);
}

void ShaderContentFactory::loadColorContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::MAIN_IMPL_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::MAIN_IMPL_F, outFragmentContent);
}

void ShaderContentFactory::loadDiffuseContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string diffuseFragment;
    FileUtils::loadFile(ShaderFiles::DIFFUSE_H_F, diffuseFragment);

    outFragmentContent = diffuseFragment + outFragmentContent;
}

void ShaderContentFactory::loadDiffuseContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string diffuseFragment;

    FileUtils::loadFile(ShaderFiles::DIFFUSE_IMPL_F, diffuseFragment);
    outFragmentContent = diffuseFragment + outFragmentContent;

    this->uncommentCode(outFragmentContent, "// [DIFFUSE] ");
}

void ShaderContentFactory::loadNormalMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string normalVertex;
    std::string normalFragment;

    FileUtils::loadFile(ShaderFiles::NORMAL_H_V, normalVertex);
    FileUtils::loadFile(ShaderFiles::NORMAL_H_F, normalFragment);

    if (this->lightData.directionalLightsCount > 0)
    {
        std::string directionalNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_DIRECTIONAL_H_V, directionalNormal);

        normalVertex = normalVertex + directionalNormal;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        std::string pointNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_POINT_H_V, pointNormal);

        normalVertex = normalVertex + pointNormal;
    }

    outVertexContent = normalVertex + outVertexContent;
    outFragmentContent = normalFragment + outFragmentContent;
}

void ShaderContentFactory::loadNormalMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string normalVertex;
    std::string normalFragment;

    FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_V, normalVertex);
    FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_F, normalFragment);

    if (this->lightData.directionalLightsCount > 0)
    {
        this->uncommentCode(normalVertex, "// [DIRECTIONAL_LIGHTS]");

        std::string directionalNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_DIRECTIONAL_IMPL_V, directionalNormal);

        normalVertex = normalVertex + directionalNormal;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        this->uncommentCode(normalVertex, "// [POINT_LIGHTS]");

        std::string pointNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_POINT_IMPL_V, pointNormal);

        normalVertex = normalVertex + pointNormal;
    }

    outVertexContent = normalVertex + outVertexContent;
    outFragmentContent = normalFragment + outFragmentContent;

    this->uncommentCode(outVertexContent, "// [NORMAL] ");
    this->uncommentCode(outFragmentContent, "// [NORMAL] ");
}

void ShaderContentFactory::loadSpecularMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string specularFragment;
    FileUtils::loadFile(ShaderFiles::SPECULAR_H_F, specularFragment);

    outFragmentContent = specularFragment + outFragmentContent;
}

void ShaderContentFactory::loadSpecularMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string specularFragment;
    FileUtils::loadFile(ShaderFiles::SPECULAR_IMPL_F, specularFragment);

    outFragmentContent = specularFragment + outFragmentContent;
    this->uncommentCode(outFragmentContent, "// [SPECULAR] ");
}

void ShaderContentFactory::loadAOMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string aoFragment;
    FileUtils::loadFile(ShaderFiles::AMBIENT_OCCLUSION_H_F, aoFragment);

    outFragmentContent = aoFragment + outFragmentContent;
}

void ShaderContentFactory::loadAOMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string aoFragment;

    FileUtils::loadFile(ShaderFiles::AMBIENT_OCCLUSION_IMPL_F, aoFragment);

    outFragmentContent = aoFragment + outFragmentContent;
    this->uncommentCode(outFragmentContent, "// [AO] ");
}

void ShaderContentFactory::loadLightsContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    FileUtils::loadFile(ShaderFiles::LIGHTS_H_V, vertexContent);
    FileUtils::loadFile(ShaderFiles::LIGHTS_H_F, fragmentContent);

    int lightsCount = this->lightData.directionalLightsCount;

    if (lightsCount > 0)
    {
        std::string directionalVertexContent;
        std::string directionalFragmentContent;
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_H_V, directionalVertexContent);
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_H_F, directionalFragmentContent);

        directionalVertexContent = StringUtils::format(directionalVertexContent, lightsCount);
        directionalFragmentContent = StringUtils::format(directionalFragmentContent, lightsCount);

        vertexContent += directionalVertexContent;
        fragmentContent += directionalFragmentContent;
    }

    lightsCount = this->lightData.pointLightsCount;
    if (lightsCount > 0)
    {
        std::string pointVertexContent;
        std::string pointFragmentContent;
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_H_V, pointVertexContent);
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_H_F, pointFragmentContent);

        pointVertexContent = StringUtils::format(pointVertexContent, lightsCount);
        pointFragmentContent = StringUtils::format(pointFragmentContent, lightsCount);

        vertexContent += pointVertexContent;
        fragmentContent += pointFragmentContent;
    }

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::loadLightsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_V, vertexContent);
    FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_F, fragmentContent);

    this->uncommentCode(outVertexContent, "// [LIGHTS]");
    this->uncommentCode(outFragmentContent, "// [LIGHTS]");

    if (this->lightData.directionalLightsCount > 0)
    {
        std::string directionalVertexContent;
        std::string directionalFragmentContent;
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_IMPL_V, directionalVertexContent);
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_IMPL_F, directionalFragmentContent);

        this->uncommentCode(vertexContent, "// [DIRECTIONAL_LIGHTS]");
        this->uncommentCode(fragmentContent, "// [DIRECTIONAL_LIGHTS]");

        vertexContent += directionalVertexContent;
        fragmentContent += directionalFragmentContent;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        std::string pointVertexContent;
        std::string pointFragmentContent;
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_IMPL_V, pointVertexContent);
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_IMPL_F, pointFragmentContent);

        this->uncommentCode(vertexContent, "// [POINT_LIGHTS]");
        this->uncommentCode(fragmentContent, "// [POINT_LIGHTS]");

        vertexContent += pointVertexContent;
        fragmentContent += pointFragmentContent;
    }

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::loadShadowsContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    if (this->lightData.directionalLightsCount > 0)
    {
        std::string directionalVertex;
        std::string directionalFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_H_V, directionalVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_H_F, directionalFragment);

        vertexContent += directionalVertex;
        fragmentContent += directionalFragment;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        std::string pointVertex;
        std::string pointFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_H_V, pointVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_H_F, pointFragment);

        vertexContent   += pointVertex;
        fragmentContent += pointFragment;
    }

    outVertexContent += vertexContent;
    outFragmentContent += fragmentContent;
}

void ShaderContentFactory::loadShadowsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    if (this->lightData.directionalLightsCount > 0)
    {
        this->uncommentCode(outVertexContent, "// [DIRECTIONAL_SHADOWS]");
        this->uncommentCode(outFragmentContent, "// [DIRECTIONAL_SHADOWS]");

        std::string directionalVertex;
        std::string directionalFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_IMPL_V, directionalVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_IMPL_F, directionalFragment);

        vertexContent += directionalVertex;
        fragmentContent += directionalFragment;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        this->uncommentCode(outVertexContent, "// [POINT_SHADOWS]");
        this->uncommentCode(outFragmentContent, "// [POINT_SHADOWS]");

        std::string pointVertex;
        std::string pointFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_IMPL_V, pointVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_IMPL_F, pointFragment);

        vertexContent += pointVertex;
        fragmentContent += pointFragment;
    }

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::uncommentCode(std::string &outShaderContent, const std::string &mark)
{
    bool result = false;

    std::size_t position = outShaderContent.find(mark);
    while (position != std::string::npos)
    {
        result = true;
        outShaderContent = outShaderContent.erase(position, mark.size());

        position = outShaderContent.find(mark, position);
    }

    if (!result)
        throw "[ShaderContentFactory] - Didn't find code mark: " + mark;
}

} // namespace
