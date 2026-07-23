#pragma once

#include <glad/glad.h>
#include <vector>


class Mesh
{
public:
    Mesh(
        const std::vector<float>& vertices
    );

    ~Mesh();


    void Draw();


private:
    GLuint vao;
    GLuint vbo;

    int vertexCount;
};