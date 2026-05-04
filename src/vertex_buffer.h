//
// Created by maelb on 02.05.2026.
//

#ifndef OPENGLPROJECT_VERTEX_BUFFER_H
#define OPENGLPROJECT_VERTEX_BUFFER_H

#include <glad/glad.h>
#include "defines.h"

struct VertexBuffer {
    VertexBuffer(void* data, uint32_t numVertices) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(struct Vertex, coords.x)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(struct Vertex, colors.r)));

        glBindVertexArray(0);
    }

    virtual ~VertexBuffer() {
        glDeleteBuffers(1, &bufferID);
    }

    void bind() {
        glBindVertexArray(vao);
    }

    void unbind() {
        glBindVertexArray(0);
    }

private:
    GLuint bufferID;
    GLuint vao;
};

#endif //OPENGLPROJECT_VERTEX_BUFFER_H