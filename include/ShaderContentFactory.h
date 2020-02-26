#ifndef _SHADER_CONTENT_FACTORY_H_
#define _SHADER_CONTENT_FACTORY_H_

#include <string>
#include <bitset>
#include "ShaderLightData.h"

namespace sre
{

class ShaderContentFactory
{
private:
    ShaderLightData lightData;

private:
    template <size_t SIZE>
    void createShaderContent
    (
        const std::bitset<SIZE> &componentsBitset, 
        std::string &outVertexContent, std::string &outFragmentContent, 
        const ShaderLightData &lightData
    );
    void createGUIShaderContent(std::string &outVertexContent, std::string &outFragmentContent);
    void createPointLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent, std::string &outGeometryContent);
    void createDirectionalLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent);
	void createPostProcessingShaderContent(std::string& outVertexContent, std::string& outFragmentContent);

    void loadColorContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadColorContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void loadDiffuseContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadDiffuseContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void loadNormalMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadNormalMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void loadSpecularMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadSpecularMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void loadAOMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadAOMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void loadLightsContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadLightsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void loadShadowsContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadShadowsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

    void uncommentCode(std::string &outShaderContent, const std::string &mark); // throws "didn't find code mark

friend class ShaderManager;
};

} // namespace

#include "ShaderContentFactory.tpp"

#endif
