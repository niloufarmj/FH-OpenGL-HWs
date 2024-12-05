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
    Circle cirecleData;
    GLfloat centerColor[3];
    GLfloat rotation;
};

struct BranchRect{
    Rectangle rect;
    GLfloat rotation;
};

struct Branch {
    std::vector<BranchRect> branchRects;
    std::vector<TriangleVertices> tris;
};

struct Tree {
    std::vector<Branch> branches;
    std::vector<Bloom> blooms;
};

std::vector<Triangle> createRectangle(Rectangle& rect, GLfloat rotation);
std::vector<Triangle> createCircle(Circle& circle);
std::vector<Triangle> createBuilding(Building& building);
std::vector<Triangle> createBush(Bush& bush);
std::vector<Triangle> createBloom(GLfloat* center, GLfloat radius, GLfloat* color, GLfloat* centerColor, int numTriangles, GLfloat rotation);
std::vector<Triangle> createTree(Tree& tree);
std::vector<Triangle> createScene();

extern Building buildings[];
extern Bush bushes[];

#endif // SHAPES_H