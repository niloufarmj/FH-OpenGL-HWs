#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include "Triangle.h"

#define BLOOM_RADIUS 0.03f
#define BLOOM_COLOR_BACK { 0.956f, 0.8f, 0.792f }
#define BLOOM_COLOR_DARK { 0.85f, 0.43f, 0.5f }
#define BLOOM_COLOR_WHITE { 1.0f, 0.98f, 0.98f }
#define BLOOM_COLOR_YELLOW { 0.98f, 0.84f, 0.76f }
#define BROWN { 0.22f, 0.17f, 0.23f }

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


struct Branch {
    GLfloat corners[4][3];
};

struct Tree {
    std::vector<Branch> branches;
    std::vector<Bloom> blooms;
};

std::vector<Triangle> createRectangle(Rectangle& rect);
std::vector<Triangle> createCircle(Circle& circle);
std::vector<Triangle> createBuilding(Building& building);
std::vector<Triangle> createBush(Bush& bush);
std::vector<Triangle> createBloom(GLfloat* center, GLfloat radius, GLfloat* color, GLfloat* centerColor, int numTriangles, GLfloat rotation);
std::vector<Triangle> createTree(Tree& tree);
std::vector<Triangle> createScene();

extern Building buildings[];
extern Bush bushes[];

#endif // SHAPES_H