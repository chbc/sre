#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include <engine/core/singletonsManager/ASingleton.h>
#include <stack>
#include <string>

namespace sre
{

class MeshComponent;
class GUIImageComponent;

struct GUIVertexData;
template <typename T> struct MeshData;

class AGraphicsWrapper : ASingleton
{
protected:
    AGraphicsWrapper() {}

    virtual void createVAO(MeshComponent *mesh) =0;
    virtual void createEBO(MeshComponent *mesh) =0;
    virtual void createGUIVAO(GUIImageComponent *guiComponent) =0;
    virtual void createGUIEBO(GUIImageComponent *guiComponent) =0;

    virtual void bindVAO(uint32_t vao, uint32_t vbo) =0;
    virtual void enableGUISettings() =0;
    virtual void enableVertexPositions() =0;
    virtual void enableVertexNormals() =0;
    virtual void enableTexCoords() =0;
    virtual void enableVertexTangents() =0;
    virtual void enableVertexBitangents() =0;
    virtual void activeDiffuseTexture(uint32_t textureId) =0;
    virtual void activeNormalTexture(uint32_t textureId) =0;
    virtual void activeSpecularTexture(uint32_t textureId) =0;
    virtual void activeAOTexture(uint32_t textureId) =0;

    virtual void setupBufferSubData(const MeshData<GUIVertexData> *meshData) =0;

    virtual void drawElement(uint32_t indicesSize) =0;

    virtual void disableVertexPositions() =0;
    virtual void disableVertexNormals() =0;
    virtual void disableTexCoords() =0;
    virtual void disableVertexTangents() =0;
    virtual void disableVertexBitangents() =0;
    virtual void disableGUISettings() =0;

    virtual void clearBuffer() =0;
    virtual uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap) =0;
    virtual uint32_t setupTexture(uint32_t width, uint32_t height, uint32_t unit) =0;
    virtual void deleteTexture(uint32_t id) =0;

    // Shaders
    virtual uint32_t loadVertexShader(const std::string &vertexContent) =0;
    virtual uint32_t loadFragmentShader(const std::string &vertexContent) =0;
    virtual uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) =0;

    virtual int getUniformLocation(uint32_t program, const std::string &varName) = 0;
    virtual void setInt(uint32_t program, int location, int value) =0;
    virtual void setFloat(uint32_t program, int location, float value) =0;
    virtual void setVec3(uint32_t program, int location, const float *value) =0;
    virtual void setVec4(uint32_t program, int location, const float *value) =0;
    virtual void setMat4(uint32_t program, int location, const float *value) =0;

    virtual void enableShader(uint32_t program) =0;
    virtual void disableShader() =0;
    virtual void releaseShader(uint32_t program, uint32_t vertShader, uint32_t fragShader) =0;
    virtual void deleteBuffers(MeshComponent *mesh) =0;
    virtual void deleteBuffers(GUIImageComponent *guiComponent) =0;

    // ###
    virtual void generateFrameBuffer(uint32_t &fbo, uint32_t textureId) =0;
    virtual void bindFrameBuffer(uint32_t fbo) =0;
    virtual void unbindFrameBuffer() =0;
    virtual void setViewport(uint32_t width, uint32_t height) =0;
    virtual void activateShadowMapTexture(uint32_t textureId) =0;
    virtual void enableFrontCullFace() =0;
    virtual void disableFrontCullFace() =0;

friend class RenderManager;
friend class ShaderManager;
friend class TextureManager;
friend class SingletonsManager;

friend class Renderer;
friend class GUIRenderer;
friend class ShadowRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
friend class ShadowRendererShaderSetup;
};

} // namespace
#endif
