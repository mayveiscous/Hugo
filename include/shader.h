#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(
        const char* vertexSource,
        const char* fragmentSource
    );

    ~Shader();

    void Use();

    GLuint ID() const;


    void SetMatrix4(
        const char* name,
        const glm::mat4& value
    );

    void SetVector3(
        const char* name,
        const glm::vec3& value
    );

    void SetFloat(
        const char* name,
        float value
    );

private:
    GLuint program;

    GLuint Compile(
        GLenum type,
        const char* source
    );
};