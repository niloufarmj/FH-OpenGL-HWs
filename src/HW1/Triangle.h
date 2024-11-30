#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <vector>

class Triangle {
public:
    Triangle(GLfloat* vertices, GLfloat* color);
    void draw() const;

    static std::vector<Triangle> createCircle(GLfloat* center, GLfloat radius, GLfloat* color, int numTriangles);
    static std::vector<Triangle> createRectangle(GLfloat* center, GLfloat width, GLfloat height, GLfloat* color);

private:
    GLfloat* vertices;
    GLfloat* color;
    unsigned int vbo[2], vao;

    void initBuffers();
};

#endif // TRIANGLE_H