#pragma once

#include <vector>
#include <framework/disable_all_warnings.h>
DISABLE_WARNINGS_PUSH()
#include "glm/vec4.hpp"
#include <glm/vec3.hpp>
DISABLE_WARNINGS_POP()

struct Light {
    glm::vec4 color;
    glm::vec4 pos;    // w unused
    glm::vec4 normal; // w unused
    int type; int _pad[3];
}; // 64B
struct Config {
    bool useMaterial = false;

    // --- Lights ---
    std::vector<Light> lights;
    size_t selectedLightIndex = 0;
};
