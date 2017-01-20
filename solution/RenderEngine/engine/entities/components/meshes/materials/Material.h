#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <engine/entities/components/AComponentsHolder.h>
#include "components/AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>
#include "components/ColorMaterialComponent.h"
#include "components/DiffuseMaterialComponent.h"

/*
namespace EMaterialMap
{

enum Type
{
	COLOR = 0x
};

}
*/

/* ###
- array de bits
- passar flags pelo construtor
- adicionar components baseado nas flags
*/

namespace sre
{

class Material : public AComponentsHolder<AMaterialComponent>
{
private:
	float shininess;

public:
	void setShininess(float shininess);
	float getShininess();

	template <typename T, typename... TArgs>
	T *addComponent(TArgs&&... mArgs)
	{
		T *newComponent{ nullptr };

		if (!AComponentsHolder<AMaterialComponent>::hasComponent<T>())
		{
			newComponent = new T{ this, std::forward<TArgs>(mArgs)... };
			AComponentsHolder<AMaterialComponent>::addComponent(newComponent);
		}
		else
			throw "Can't add duplicate component!";

		return newComponent;
	}

private:
	Material(float shininess = 15.0);

friend class MeshComponent;
};

} // namespace

#endif
