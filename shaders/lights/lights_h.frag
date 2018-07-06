// LIGHTS_H //

// Types
struct DirectionalLight
{
	vec3 color;
};

struct PointLight
{
    vec3 color;
    float range;
    float intensity;
};

struct LightSources
{
    DirectionalLight directionalLights[4]; 
    int directionalLightsCount;

    PointLight pointLights[4];
    int pointLightsCount;

    vec3 ambientLightColor;
};

// Uniform variables
uniform LightSources lights;
uniform float shininess;

// Varying variables
in vec3 var_toPointLightVectors[4];
in vec3 var_directionalLightVectors[4];

// Functions
vec3 Lights_computeAmbientLight(vec3 materialColor);
void Lights_computeDiffuseAndSpecularLights(inout vec3 kd, inout vec3 ks);
void Lights_computeDirectionalLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);
void Lights_computePointLights(vec3 normal, vec3 toCameraDirection, inout vec3 kd, inout vec3 ks);

void Lights_computeEnergies(vec3 normal, vec3 toCameraDirection, vec3 toLightVector, inout float diffuseEnergy, inout float specularEnergy);
float Lights_getAttenuation(int lightIndex);
