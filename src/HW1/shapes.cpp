#include "Shapes.h"


// Define buildings and their windows
Building buildings[] = {
    // Building 1
    { 
        { {0.61f, -0.45f, 0.0f}, 0.22f, 0.38f, {0.9f, 0.75f, 0.72f} }, // Building rectangle
        { 
            { {0.57f, -0.35f, 0.0f}, 0.02f, 0.071f, {0.92f, 0.79f, 0.78f} }, // Window 1
            { {0.65f, -0.35f, 0.0f}, 0.02f, 0.071f, {0.92f, 0.79f, 0.78f} }, // Window 2
            { {0.57f, -0.45f, 0.0f}, 0.02f, 0.071f, {0.92f, 0.79f, 0.78f} }, // Window 3
            { {0.65f, -0.45f, 0.0f}, 0.02f, 0.071f, {0.92f, 0.79f, 0.78f} }, // Window 4
            { {0.57f, -0.55f, 0.0f}, 0.02f, 0.071f, {0.92f, 0.79f, 0.78f} }, // Window 5
            { {0.65f, -0.55f, 0.0f}, 0.02f, 0.071f, {0.92f, 0.79f, 0.78f} } // Window 6
        } 
    },
    // Building 2
    { 
        { {0.21f, -0.49f, 0.0f}, 0.18f, 0.29f, {0.96f, 0.73f, 0.69f} }, // Building rectangle
        {
            { {0.16f, -0.4f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 1
            { {0.22f, -0.4f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 2
            { {0.26f, -0.4f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 3
            { {0.16f, -0.46f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 4
            { {0.22f, -0.46f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 5
            { {0.26f, -0.46f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 6
            { {0.16f, -0.52f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 7
            { {0.22f, -0.52f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 8
            { {0.26f, -0.52f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 9
            { {0.16f, -0.58f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 10
            { {0.22f, -0.58f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 11
            { {0.26f, -0.58f, 0.0f}, 0.015f, 0.04f, {0.96f, 0.81f, 0.78f} }, // Window 12
        } 
    },
    // Building 3
    { 
        { {-0.13f, -0.43f, 0.0f}, 0.34f, 0.41f, {0.96f, 0.79f, 0.72f} }, // Building rectangle
        {
            { {-0.19f, -0.35f, 0.0f}, 0.08f, 0.071f, {0.96f, 0.75f, 0.68f} }, // Window 1
            { {-0.1f, -0.35f, 0.0f}, 0.05f, 0.071f, {0.96f, 0.75f, 0.68f} }, // Window 2
            { {-0.03f, -0.35f, 0.0f}, 0.05f, 0.071f, {0.96f, 0.75f, 0.68f} }, // Window 3
            { {-0.19f, -0.45f, 0.0f}, 0.08f, 0.071f, {0.96f, 0.75f, 0.68f} }, // Window 4
            { {-0.1f, -0.45f, 0.0f}, 0.05f, 0.071f, {0.96f, 0.75f, 0.68f} }, // Window 5
            { {-0.03f, -0.45f, 0.0f}, 0.05f, 0.071f, {0.96f, 0.75f, 0.68f} }, // Window 6
            { {-0.19f, -0.58f, 0.0f}, 0.08f, 0.11f, {0.96f, 0.75f, 0.68f} } // Door
        } 
    },
    // Building 4
    { 
        { {-0.58f, -0.46f, 0.0f}, 0.21f, 0.34f, {0.92f, 0.79f, 0.78f} }, // Building rectangle
        {
            { {-0.58f, -0.32f, 0.0f}, 0.21f, 0.055f, {0.96f, 0.83f, 0.81f} }, // Roof
            { {-0.62f, -0.42f, 0.0f}, 0.05f, 0.06f, {0.95f, 0.71f, 0.72f} }, // Window 1
            { {-0.54f, -0.42f, 0.0f}, 0.05f, 0.06f, {0.95f, 0.71f, 0.72f} }, // Window 2
            { {-0.58f, -0.573f, 0.0f}, 0.08f, 0.11f, {0.78f, 0.69f, 0.7f} } // Door
        } 
    }
};

// Define bushes
Bush bushes[] = {
    { 
        { 
            { {0.34f, -0.635f, 0.0f,
               0.33f, -0.56f, 0.0f,
               0.39f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 1
            { {0.355f, -0.635f, 0.0f,
               0.36f, -0.5f, 0.0f,
               0.42f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 2
            { {0.43f, -0.635f, 0.0f,
               0.435f, -0.51f, 0.0f,
               0.36f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 3
            { {0.4f, -0.635f, 0.0f,
               0.45f, -0.57f, 0.0f,
               0.44f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 4
        }
    },
    {
        { 
            { {-0.24f, -0.635f, 0.0f,
               -0.23f, -0.56f, 0.0f,
               -0.29f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 1
            { {-0.255f, -0.635f, 0.0f,
               -0.26f, -0.5f, 0.0f,
               -0.32f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 2
            { {-0.33f, -0.635f, 0.0f,
               -0.335f, -0.51f, 0.0f,
               -0.26f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 3
            { {-0.3f, -0.635f, 0.0f,
               -0.35f, -0.57f, 0.0f,
               -0.34f, -0.635f, 0.0f}, 
              {0.49f, 0.82f, 0.54f} 
            }, // Triangle 4
        } 
    }
};


// Define tree data 
Tree tree = {
    {
        {
            {
                {-0.12f, -0.635f, 0.0f}, {-0.01f, 0.82f, 0.0f}, {0.01f, 0.82f, 0.0f}, {0.12f, -0.635f, 0.0f}
            }
        },
    },
    {
        {
            {{ 0.01f, 0.77f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 20},
            BLOOM_COLOR_DARK,
            -20
        }
    }
};

std::vector<Triangle> createRectangle(Rectangle& rect) {
    return Triangle::createRectangle(rect.center, rect.width, rect.height, rect.color);
}

std::vector<Triangle> createCircle(Circle& circle) {
    return Triangle::createCircle(circle.center, circle.radius, circle.color, circle.numTriangles);
}

std::vector<Triangle> createBush(Bush& bush) {
    std::vector<Triangle> triangles;
    for (auto& tri : bush.triangles) {
        triangles.emplace_back(tri.vertices, tri.color);
    }
    return triangles;
}

std::vector<Triangle> createBuilding(Building& building) {
    std::vector<Triangle> triangles = createRectangle(building.buildingRect);
    for (auto& window : building.windowsRects) {
        std::vector<Triangle> windowTriangles = createRectangle(window);
        triangles.insert(triangles.end(), windowTriangles.begin(), windowTriangles.end());
    }
    return triangles;
}

std::vector<Triangle> createTree(Tree& tree) {
    std::vector<Triangle> triangles;

    for (auto& branch : tree.branches) {
        GLfloat color[] = BROWN;
        std::vector<Triangle> branchRectTriangles = Triangle::createQuad(branch.corners[0], branch.corners[1], branch.corners[2], branch.corners[3], color);
        triangles.insert(triangles.end(), branchRectTriangles.begin(), branchRectTriangles.end());
    }

    for (auto& bloom : tree.blooms) {
        std::vector<Triangle> bloomTriangles = createBloom(bloom.cirecleData.center, bloom.cirecleData.radius, bloom.cirecleData.color, bloom.centerColor, bloom.cirecleData.numTriangles, bloom.rotation);
        triangles.insert(triangles.end(), bloomTriangles.begin(), bloomTriangles.end());
    }

    return triangles;
}


std::vector<Triangle> createBloom(
    GLfloat* center, 
    GLfloat radius, 
    GLfloat* color, 
    GLfloat* centerColor, 
    int numTriangles, 
    GLfloat rotation
) {
    std::vector<Triangle> triangles;

    // Center petal
    auto centerPetal = Triangle::createCircle(center, radius, color, numTriangles);
    triangles.insert(triangles.end(), centerPetal.begin(), centerPetal.end());

    // Positions of petals relative to the center
    GLfloat petalOffsets[4][2] = {
        { -radius, 0.0f },  // Left
        { radius, 0.0f },   // Right
        { 0.0f, radius },   // Top
        { 0.0f, -radius }   // Bottom
    };

    for (const auto& offset : petalOffsets) {
        GLfloat petalCenter[3] = {
            center[0] + offset[0],
            center[1] + offset[1],
            center[2]
        };

        // Apply rotation
        Triangle::rotatePoint(petalCenter[0], petalCenter[1], center[0], center[1], rotation);

        // Create petal
        auto petal = Triangle::createCircle(petalCenter, radius, color, numTriangles);
        triangles.insert(triangles.end(), petal.begin(), petal.end());
    }

    // Small center circle
    auto centerCircle = Triangle::createCircle(center, radius / 3, centerColor, numTriangles);
    triangles.insert(triangles.end(), centerCircle.begin(), centerCircle.end());

    return triangles;
}

std::vector<Triangle> createScene() {
    std::vector<Triangle> triangles;

    // Create buildings and add to triangles
    for (auto& building : buildings) {
        std::vector<Triangle> buildingTriangles = createBuilding(building);
        triangles.insert(triangles.end(), buildingTriangles.begin(), buildingTriangles.end());
    }

    // Create bushes and add to triangles
    for (auto& bush : bushes) {
        std::vector<Triangle> bushTriangles = createBush(bush);
        triangles.insert(triangles.end(), bushTriangles.begin(), bushTriangles.end());
    }

    GLfloat center_buttomLine[] = { 0.0f, -0.66f, 0.0f };
    GLfloat width_buttomLine = 2.0f;
    GLfloat height_buttomLine = 0.065f;
    GLfloat color_buttomLine[] = BROWN;
    std::vector<Triangle> buttomLine = Triangle::createRectangle(center_buttomLine, width_buttomLine, height_buttomLine, color_buttomLine);
    triangles.insert(triangles.end(), buttomLine.begin(), buttomLine.end());

    std::vector<Triangle> treeTriangles = createTree(tree);
    triangles.insert(triangles.end(), treeTriangles.begin(), treeTriangles.end());
    
    return triangles;
}