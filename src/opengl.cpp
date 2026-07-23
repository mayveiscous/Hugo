#include "opengl.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>


static GLFWwindow* g_window = nullptr;


static void glfwErrorCallback(int error, const char* desc) {
    std::cerr 
        << "GLFW Error [" 
        << error 
        << "]: " 
        << desc 
        << std::endl;
}


namespace OpenGL {

bool Init(int width, int height, const char* title) {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    g_window = glfwCreateWindow(
        width,
        height,
        title,
        nullptr,
        nullptr
    );

    if (!g_window) {
        glfwTerminate();
        return false;
    }


    glfwMakeContextCurrent(g_window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(g_window);
        glfwTerminate();
        return false;
    }


    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );


    return true;
}


void Shutdown() {
    if (g_window)
    {
        glfwDestroyWindow(g_window);
        g_window = nullptr;
    }

    glfwTerminate();
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
}


void EndFrame() {
    glfwSwapBuffers(g_window);
}


bool ShouldClose() {
    return glfwWindowShouldClose(g_window);
}


void PollEvents() {
    glfwPollEvents();
}


GLFWwindow* GetWindow() {
    return g_window;
}
}