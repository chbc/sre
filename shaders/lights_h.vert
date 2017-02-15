// LIGHTS_H //

// Types
struct PointLight
{
	vec3 position;
};

struct LightSources
{
	PointLight pointLights[4];
	int pointLightsCount;
};

// Lights
uniform LightSources lights;

// Varying variables
out vec3 var_toPointLightVectors[4];

void Lights_setup(vec3 vertexPosition);