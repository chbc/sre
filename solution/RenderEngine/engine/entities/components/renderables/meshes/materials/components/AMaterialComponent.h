#ifndef _A_MATERIAL_COMPONENT_H_
#define _A_MATERIAL_COMPONENT_H_

namespace sre
{

class Material;

class AMaterialComponent
{

protected:
    Material * material;

public:
    virtual ~AMaterialComponent() {}

protected:
	AMaterialComponent(Material *material) : material(material) {}
};

}

#endif
