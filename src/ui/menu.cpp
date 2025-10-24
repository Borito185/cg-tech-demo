//
// Created by boris on 22-10-2025.
//

#include "menu.h"

#include <format>
#include <string>

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"

Menu::Menu(Config &config) : m_config(config) {}

void Menu::draw() {
    ImGui::Begin("Controls");

    ImGui::Text("Material");
    ImGui::Separator();
    drawMaterialControls();

    ImGui::Text("Lights");
    ImGui::Separator();
    drawLightControls();

    ImGui::End();
}

void Menu::drawMaterialControls() {
    ImGui::Checkbox("Use material if no texture", &m_config.useMaterial);
}

void Menu::drawLightControls() {
    if (ImGui::BeginListBox("Lights")) {
        for (size_t i = 0; i < m_config.lights.size(); ++i) {
            bool selected = (i == m_config.selectedLightIndex);
            if (ImGui::Selectable(("Light " + std::to_string(i)).c_str(), selected))
                m_config.selectedLightIndex = i;
        }
        ImGui::EndListBox();
    }

    Light* light = &m_config.lights[m_config.selectedLightIndex];

    static constexpr const char* LIGHT_TYPES[] = {
        "None",
        "Point",
        "Directional",
        "Spot"
    };

    if (ImGui::BeginListBox("Type")) {
        for (int i = 0; i < 4; ++i) {
            bool selected = (i == light->type);
            if (ImGui::Selectable(LIGHT_TYPES[i], selected))
                light->type = i;
        }
        ImGui::EndListBox();
    }
    ImGui::ColorEdit4("Color", glm::value_ptr(light->color));
    if (light->type == 1 || light->type == 3) {
        ImGui::InputFloat3("Position", glm::value_ptr(light->pos));
    }
    if (light->type == 2 || light->type == 3) {
        ImGui::InputFloat3("Direction", glm::value_ptr(light->normal));
    }

    if (ImGui::Button("New")) {
        m_config.lights.emplace_back();
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove")) {
        m_config.lights.erase(static_cast<int>(m_config.selectedLightIndex) + m_config.lights.begin());
    }
}

