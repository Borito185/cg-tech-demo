//
// Created by boris on 22-10-2025.
//

#pragma once
#include <utils/config.h>

class Menu {
public:
    Menu(Config& config);

    void draw();

private:
    Config& m_config;
    // --- Menu Sections ---
    void drawMaterialControls();
    void drawLightControls();
};