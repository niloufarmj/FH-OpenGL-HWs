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
        } // No windows
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

std::vector<Triangle> createRectangle(Rectangle& rect) {
    return Triangle::createRectangle(rect.center, rect.width, rect.height, rect.color);
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

std::vector<Triangle> createScene() {
    std::vector<Triangle> triangles;

    // Create a circle
    GLfloat center[] = { 0.0f, 0.0f, 0.0f };
    GLfloat radius = 0.3f;
    GLfloat circleColor[] = { 0.0f, 1.0f, 1.0f };  // cyan
    int numTriangles = 30; // You can change this value to create a circle with a different number of triangles
    std::vector<Triangle> circle = Triangle::createCircle(center, radius, circleColor, numTriangles);
    triangles.insert(triangles.end(), circle.begin(), circle.end());

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

    return triangles;
}