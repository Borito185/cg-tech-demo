//
// Created by boris on 22-10-2025.
//

#include "menu.h"

#include "imgui/imgui.h"

Menu::Menu(Config &config) : m_config(config) {}

void Menu::draw() {
    ImGui::Begin("Controls");

    ImGui::Text("Material");
    ImGui::Separator();
    drawMaterialControls();

    ImGui::End();
}

void Menu::drawMaterialControls() {
    ImGui::Checkbox("Use material if no texture", &m_config.useMaterial);
}

