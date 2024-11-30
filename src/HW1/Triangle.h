#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <iostream>
#include <vector>

class Triangle {
public:
    Triangle(GLfloat* vertices, GLfloat* color);
    void draw() const;

private:
    GLfloat* vertices;
    GLfloat* color;
    unsigned int vbo[2], vao;

    void initBuffers();
};

#endif // TRIANGLE_H