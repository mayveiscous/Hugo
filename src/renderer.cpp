#include "renderer.h"
#include "shader.h"
#include "mesh.h"

#include <unordered_map>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static Shader* shader = nullptr;

static std::unordered_map<int, Mesh*> meshes;
static int nextMeshId = 1;

static glm::vec3 cameraPosition = {0, 0, 3};
static glm::vec3 cameraTarget = {0, 0, 0};


static const char* vertexShader = R"(
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";


static const char* fragmentShader = R"(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
)";


namespace Renderer {

bool Init() {
    shader = new Shader(
        vertexShader,
        fragmentShader
    );

    return true;
}


int CreateMesh(const std::vector<float>& vertices) {
    int id = nextMeshId++;

    meshes[id] = new Mesh(vertices);

    return id;
}


void BeginFrame() {
    glClearColor(
        0.1f,
        0.1f,
        0.15f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );


    shader->Use();


    glm::mat4 view = glm::lookAt(
        cameraPosition,
        cameraTarget,
        glm::vec3(0, 1, 0)
    );


    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        500.0f
    );


    shader->SetMatrix4(
        "view",
        view
    );

    shader->SetMatrix4(
        "projection",
        projection
    );
}


void DrawMesh(int id, glm::vec3 position) {
    auto it = meshes.find(id);

    if (it == meshes.end())
        return;


    shader->Use();


    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        position
    );


    shader->SetMatrix4(
        "model",
        model
    );


    it->second->Draw();
}


void EndFrame() {

}

}