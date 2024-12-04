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

struct Circle {
    GLfloat center[3];
    GLfloat radius;
    GLfloat color[3];
    int numTriangles; 
};

struct Bloom {
    std::vector<Circle> petals;
    Circle centerCircle;
};

struct Branch {
    std::vector<Rectangle> rects;
    std::vector<TriangleVertices> tris;
};

struct Tree {
    std::vector<Branch> branches;
    std::vector<Bloom> blooms;
};

std::vector<Triangle> createRectangle(Rectangle& rect);
std::vector<Triangle> createCircle(Circle& circle);
std::vector<Triangle> createBuilding(Building& building);
std::vector<Triangle> createBush(Bush& bush);
std::vector<Triangle> createTree(Tree& tree);
std::vector<Triangle> createScene();

extern Building buildings[];
extern Bush bushes[];

#endif // SHAPES_H