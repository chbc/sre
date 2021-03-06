#include "MaterialEditorProperty.h"
#include "Material.h"

#include <imgui/imgui.h>

namespace sre
{

MaterialEditorProperty::MaterialEditorProperty(const char* title, Material* arg_material)
	: AEditorProperty(title), material(arg_material)
{ }

void MaterialEditorProperty::draw()
{
	for (const auto& component : this->material->componentsMap)
	{
		const char* componentName = component.second->getClassName();
		if (ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& property : component.second->editorProperties)
			{
				property->draw();
			}
			// XXX ImGui::Separator();
			ImGui::TreePop();
		}
	}
}

} // namespace
