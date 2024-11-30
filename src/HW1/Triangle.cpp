#include "Triangle.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Triangle::Triangle(GLfloat* vertices, GLfloat* color) {
    this->vertices = vertices;
    this->color = color;
    initBuffers();
}

void Triangle::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::initBuffers() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(2, vbo);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Color buffer
    GLfloat colors[9] = { color[0], color[1], color[2], color[0], color[1], color[2], color[0], color[1], color[2] };
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindVertexArray(0); // disable VBO
}

std::vector<Triangle> Triangle::createCircle(GLfloat* center, GLfloat radius, GLfloat* color, int numTriangles) {
    std::vector<Triangle> triangles;
    const float angleIncrement = 2.0f * M_PI / numTriangles;

    for (int i = 0; i < numTriangles; ++i) {
        GLfloat vertices[9];
        vertices[0] = center[0];
        vertices[1] = center[1];
        vertices[2] = center[2];

        vertices[3] = center[0] + radius * cos(i * angleIncrement);
        vertices[4] = center[1] + radius * sin(i * angleIncrement);
        vertices[5] = center[2];

        vertices[6] = center[0] + radius * cos((i + 1) * angleIncrement);
        vertices[7] = center[1] + radius * sin((i + 1) * angleIncrement);
        vertices[8] = center[2];

        triangles.emplace_back(vertices, color);
    }

    return triangles;
}