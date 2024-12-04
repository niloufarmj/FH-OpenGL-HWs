#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include "Triangle.h"

struct Rectangle {
    GLfloat center[3];
    GLfloat width;
    GLfloat height;
    GLfloat color[3];
};

struct Building {
    Rectangle buildingRect;
    std::vector<Rectangle> windowsRects;
};

struct TriangleVertices {
    GLfloat vertices[9];
    GLfloat color[3];
};

struct Bush {
    std::vector<TriangleVertices> triangles;
};

std::vector<Triangle> createRectangle(Rectangle& rect);
std::vector<Triangle> createBuilding(Building& building);
std::vector<Triangle> createBush(Bush& bush);
std::vector<Triangle> createScene();

extern Building buildings[];
extern Bush bushes[];

#endif // SHAPES_H