#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorMenuBar.h"
#include "EngineValues.h"
#include "imgui/imgui.h"

namespace sre
{

EditorMenuBar::EditorMenuBar(bool* editorEnabled, bool* demoEnabled) 
	: isEditorEnabled(editorEnabled), isDemoEnabled(demoEnabled) { }

void EditorMenuBar::onEditorGUI()
{
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(EngineValues::SCREEN_WIDTH, 10));

	ImGui::Begin
	(
		"Menu", nullptr,
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoMove
	);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New scene");
			ImGui::MenuItem("Open scene");
			ImGui::MenuItem("Save scene");
			ImGui::MenuItem("Save scene as");
			if (ImGui::MenuItem("Exit"))
				*this->isEditorEnabled = false;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Preferences");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("ImGui Demo"))
				*this->isDemoEnabled = true;

			ImGui::MenuItem("About");
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	ImGui::End();
}

} // namespace

#endif
