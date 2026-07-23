#include <hugo.h>
#include <opengl.h>
#include <renderer.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int lua_init(lua_State* L) {
    int width = luaL_checknumber(L, 1);
    int height = luaL_checknumber(L, 2);
    const char* title = luaL_checkstring(L, 3);

    if (!OpenGL::Init(width, height, title)) {
        return 0;
    }

    Renderer::Init();
    return 0;
}

int lua_createMesh(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);

    std::vector<float> vertices;
    int length = lua_rawlen(L, 1);

    for (int i = 1; i <= length; i++) {
        lua_rawgeti(L, 1, i);

        vertices.push_back(lua_tonumber(L, -1));

        lua_pop(L, 1);
    }

    int id = Renderer::CreateMesh(vertices);

    lua_pushinteger(L, id);

    return 1;
}

int lua_drawMesh(lua_State* L) {
    int id = luaL_checkinteger(L, 1);

    glm::vec3 position = {
        (float)luaL_optnumber(L, 2, 0),
        (float)luaL_optnumber(L, 3, 0),
        (float)luaL_optnumber(L, 4, 0)
    };

    Renderer::DrawMesh(id, position);

    return 0;
}

int lua_beginFrame(lua_State* L) {
    Renderer::BeginFrame();
    
    return 0;
}

int lua_endFrame(lua_State* L) {
    OpenGL::EndFrame();
    return 0;
}

int lua_pollEvents(lua_State* L) {
    OpenGL::PollEvents();
    return 0;
}

int lua_shouldClose(lua_State* L) {
    lua_pushboolean(L, OpenGL::ShouldClose());
    return 1;
}


static const luaL_Reg methods[] = {
    // setup
    {"init", lua_init},

    // window
    {"beginFrame", lua_beginFrame},
    {"endFrame", lua_endFrame},
    {"pollEvents", lua_pollEvents},
    {"shouldClose", lua_shouldClose},

    // mesh
    {"createMesh", lua_createMesh},
    {"drawMesh", lua_drawMesh},
    {nullptr, nullptr}
};

extern "C" int luaopen_hugo(lua_State* L) {
    luaL_newlib(L, methods);
    return 1;
}