#pragma once

struct GLFWwindow;

namespace OpenGL {
    bool Init(int width, int height, const char* title);
    void Shutdown();

    void BeginFrame();
    void EndFrame();

    bool ShouldClose();
    void PollEvents();

    GLFWwindow* GetWindow();
}