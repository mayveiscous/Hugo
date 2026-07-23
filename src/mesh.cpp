#include "mesh.h"

Mesh::Mesh(const std::vector<float>& vertices) {
    vertexCount = vertices.size() / 3;

    glGenVertexArrays(
        1,
        &vao
    );

    glGenBuffers(
        1,
        &vbo
    );


    glBindVertexArray(vao);


    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );


    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        false,
        3 * sizeof(float),
        nullptr
    );


    glEnableVertexAttribArray(0);


    glBindBuffer(
        GL_ARRAY_BUFFER,
        0
    );

    glBindVertexArray(0);
}



Mesh::~Mesh() {
    glDeleteVertexArrays(
        1,
        &vao
    );

    glDeleteBuffers(
        1,
        &vbo
    );
}



void Mesh::Draw() {
    glBindVertexArray(vao);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexCount
    );

    glBindVertexArray(0);
}