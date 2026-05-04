//
// Created by maelb on 04.05.2026.
//

#ifndef OPENGLPROJECT_INDEX_BUFFER_H
#define OPENGLPROJECT_INDEX_BUFFER_H

#include <glad/glad.h>
#include "defines.h"

struct IndexBuffer {
    IndexBuffer(void* data, uint32_t numIndices, uint8_t elementSize) {

        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);

    }

    virtual ~IndexBuffer() {
        glDeleteBuffers(1, &bufferID);
    }

    void bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    }

    void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }

private:
    GLuint bufferID;
};

#endif //OPENGLPROJECT_INDEX_BUFFER_H