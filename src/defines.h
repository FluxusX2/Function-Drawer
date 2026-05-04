//
// Created by maelb on 04.05.2026.
//

#ifndef FUNCTIONDRAWING_DEFINES_H
#define FUNCTIONDRAWING_DEFINES_H
#include "glm/glm.hpp"

struct Vertex {
    glm::vec2 coords{};
    glm::vec4 colors{};

    Vertex() {

    }

    Vertex(glm::vec2 vec, glm::vec4 vec4) {
        this->coords = vec;
        this->colors = vec4;
    };
};

#endif //FUNCTIONDRAWING_DEFINES_H