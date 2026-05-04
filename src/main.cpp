#include <iostream>
#include <SDL3/SDL_init.h>
#include "SDL3/SDL_timer.h"
#include <SDL3/SDL.h>

#include "glad/glad.h"
#include <glm/glm.hpp>

#include "defines.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"
#include "computingFunc.h"


int main() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        std::cerr << "Error: SDL could not be initialized.";
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);


    //SPECIFIC VERSION FOR MACOS
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    uint32_t flags = SDL_WINDOW_OPENGL;
    SDL_Window *window = SDL_CreateWindow("Function Drawer", 800, 600, flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cerr << "Error: Failed to intialize GLAD";
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    Vertex vertices[128];
    uint32_t numVertices = 0;
    uint32_t indices[128];
    uint32_t numIndices = 0;

    float start = -10.f;
    float step = 20.f / 128.f;

    for (int i = 0; i < 128; i++) {
        float x = start + (float)i * step;
        float y = quadraticFunc(x) / 10.f;
        x /= 10.f;

        vertices[i] = Vertex(glm::vec2(x, y), glm::vec4(1.f, 1.f, 1.f, 1.f));
        indices[i] = i;
        numIndices++;
        numVertices++;
    }

    IndexBuffer indexBuffer(indices, numIndices, sizeof(indices[0]));

    //Vertexbuffer wird erstellt, gebindet und daten werden gezeichnet.
    VertexBuffer vertexBuffer(vertices, numVertices);
    vertexBuffer.unbind();

    Shader shader("../shaders/basic.vert", "../shaders/basic.frag");
    shader.bind();

    uint64_t perfCounterFrequency = SDL_GetPerformanceFrequency();
    uint64_t lastCounter = SDL_GetPerformanceCounter();

    float delta = 0.f;

    bool close = false;
    while (!close) {

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertexBuffer.bind();
        indexBuffer.bind();
        glDrawElements(GL_LINE_STRIP, numIndices, GL_UNSIGNED_INT, nullptr);
        indexBuffer.unbind();
        vertexBuffer.unbind();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        SDL_GL_SwapWindow(window);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                close = true;
            }
        }

        uint64_t endCounter = SDL_GetPerformanceCounter();
        uint64_t counterElapsed = endCounter - lastCounter;
        delta = ((float)counterElapsed) / ((float)perfCounterFrequency);
        uint32_t FPS = perfCounterFrequency / counterElapsed;
        std::string title = "Cool window - FPS: " + std::to_string(FPS);
        SDL_SetWindowTitle(window, title.c_str());
        lastCounter = endCounter;
    }
}
