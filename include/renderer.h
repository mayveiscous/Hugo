#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Renderer {

bool Init();

int CreateMesh(const std::vector<float>& vertices);

void BeginFrame();

void DrawMesh(
    int id,
    glm::vec3 position
);

void EndFrame();

}