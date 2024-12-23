#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>

class Triangle {
public:
    Triangle(GLfloat* vertices, GLfloat* color);
    void draw(const glm::mat4& transform = glm::mat4(1.0f)) const;
    static void rotatePoint(GLfloat& x, GLfloat& y, GLfloat cx, GLfloat cy, GLfloat angle);

    static std::vector<Triangle> createCircle(GLfloat* center, GLfloat radius, GLfloat* color, int numTriangles);
    static std::vector<Triangle> createRectangle(GLfloat* center, GLfloat width, GLfloat height, GLfloat* color);
    static std::vector<Triangle> createQuad(GLfloat* p1, GLfloat* p2, GLfloat* p3, GLfloat* p4, GLfloat* color);
    static GLfloat sign(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
    bool isPointInside(GLfloat x, GLfloat y) const;

private:
    GLfloat* vertices;
    GLfloat* color;
    unsigned int vbo[2], vao;

    void initBuffers();
};

#endif // TRIANGLE_H