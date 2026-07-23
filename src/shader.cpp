#include "shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    GLuint vertex = Compile(
        GL_VERTEX_SHADER,
        vertexSource
    );

    GLuint fragment = Compile(
        GL_FRAGMENT_SHADER,
        fragmentSource
    );


    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);


    GLint success;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );


    if (!success) {
        char log[512];

        glGetProgramInfoLog(
            program,
            512,
            nullptr,
            log
        );

        std::cerr
            << "Shader link error:\n"
            << log
            << std::endl;
    }


    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(program);
}

GLuint Shader::Compile(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);

    glShaderSource(
        shader,
        1,
        &source,
        nullptr
    );


    glCompileShader(shader);


    GLint success;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );


    if (!success)
    {
        char log[512];

        glGetShaderInfoLog(
            shader,
            512,
            nullptr,
            log
        );

        std::cerr
            << "Shader compile error:\n"
            << log
            << std::endl;
    }


    return shader;
}



void Shader::Use() {
    glUseProgram(program);
}



GLuint Shader::ID() const {
    return program;
}



void Shader::SetMatrix4(const char* name, const glm::mat4& value) {
    glUniformMatrix4fv(
        glGetUniformLocation(program, name),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}



void Shader::SetVector3(const char* name, const glm::vec3& value) {
    glUniform3f(
        glGetUniformLocation(program, name),
        value.x,
        value.y,
        value.z
    );
}



void Shader::SetFloat(const char* name, float value) {
    glUniform1f(
        glGetUniformLocation(program, name),
        value
    );
}