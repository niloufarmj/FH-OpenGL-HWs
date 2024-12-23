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


Tree tree = {
    {
        { // Trunk
            {
                {-0.012f, 0.82f, 0.0f}, 
                {0.012f, 0.82f, 0.0f}, 
                {-0.12f, -0.635f, 0.0f}, 
                {0.12f, -0.635f, 0.0f}
            },
            
        },
        { // Branch Bottom Right
            {
                {0.067f, -0.210f, 0.0f}, 
                {0.0702f, -0.306f, 0.0f},
                {0.226f, -0.095f, 0.0f},
                {0.258f, -0.134f, 0.0f}
            }
        },
        { // Branch Bottom Right
            {
                { 0.230f, 0.010f, 0.0f }, 
                { 0.256f, 0.006f, 0.0f },
                { 0.185f, -0.144f, 0.0f },
                { 0.240f, -0.150f, 0.0f }
            }
        },
        { // Branch Bottom Right
            {
                { 0.195f, -0.121f, 0.0f },
                { 0.42f, -0.086f, 0.0f },
                { 0.201f, -0.182f, 0.0f },
                { 0.4f, -0.135f, 0.0f }
            }
        },
        { // Branch Bottom Right
            {
                { 0.4f, -0.088f, 0.0f },
                { 0.601f, -0.112f, 0.0f },
                { 0.39f, -0.139f, 0.0f },
                { 0.588f, -0.137f, 0.0f },
            }
        },
        { // Branch Bottom Right
            {
                { 0.56f, -0.115f, 0.0f },
                { 0.716f, -0.058f, 0.0f },
                { 0.578f, -0.1382f, 0.0f },
                { 0.73f, -0.08f, 0.0f },
            }
        },
        { // Branch Bottom Right
            {
                { 0.508f, 0.019f, 0.0f },
                { 0.524f, 0.000f, 0.0f },
                { 0.394f, -0.109f, 0.0f },
                { 0.460f, -0.112f, 0.0f }
            }
        },
        { // Branch Middle 1 Right
            {
                { 0.042f, 0.058f, 0.0f },
                { 0.361f, 0.265f, 0.0f },
                { 0.054f, -0.048f, 0.0f },
                { 0.415f, 0.220f, 0.0f }
            }
        },
        { // Branch Middle 1 Right
            {
                { 0.173f, 0.300f, 0.0f },
                { 0.195f, 0.304f, 0.0f },
                { 0.131f, 0.109f, 0.0f },
                { 0.179f, 0.105f, 0.0f },
            }
        },
        { // Branch Middle 1 Right
            {
                { 0.240f, 0.102f, 0.0f },
                { 0.288f, 0.150f, 0.0f },
                { 0.428f, 0.096f, 0.0f },
                { 0.428f, 0.128f, 0.0f },
            }
        },
        {
            {
                { 0.288f, 0.188f, 0.0f },
                { 0.307f, 0.374f, 0.0f },
                { 0.304f, 0.182f, 0.0f },
                { 0.332f, 0.383f, 0.0f }
            }
        },
        {
            {
                { 0.323f, 0.415f, 0.0f },
                { 0.466f, 0.457f, 0.0f },
                { 0.329f, 0.390f, 0.0f },
                { 0.486f, 0.441f, 0.0f }
            }
        },
        {
            {
                { 0.409f, 0.227f, 0.0f },
                { 0.486f, 0.268f, 0.0f },
                { 0.438f, 0.195f, 0.0f },
                { 0.508f, 0.252f, 0.0f }
            }
        },
        {
            {
                { 0.482f, 0.332f, 0.0f },
                { 0.498f, 0.441f, 0.0f },
                { 0.518f, 0.307f, 0.0f },
                { 0.524f, 0.425f, 0.0f },

            }
        },
        { // Branch Middle 2 Right
            {
                { 0.026f, 0.288f, 0.0f },
                { 0.192f, 0.473f, 0.0f },
                { 0.029f, 0.192f, 0.0f },
                { 0.211f, 0.447f, 0.0f },
            }
        },
        {
            {
                { 0.185f, 0.470f, 0.0f },
                { 0.256f, 0.466f, 0.0f },
                { 0.169f, 0.396f, 0.0f },
                { 0.259f, 0.460f, 0.0f }
            }
        },
        { // Branch Middle 3 Right
            {
                { 0.032f, 0.422f, 0.0f },
                { 0.243f, 0.642f, 0.0f },
                { 0.032f, 0.358f, 0.0f },
                { 0.236f, 0.613f, 0.0f },
            }
        },
        { // Branch Top Right
            {
                { 0.019f, 0.524f, 0.0f },
                { 0.070f, 0.613f, 0.0f },
                { 0.032f, 0.470f, 0.0f },
                { 0.102f, 0.613f, 0.0f } 
            }
        },
        { // Branch Top Right
            {
                { 0.080f, 0.639f, 0.0f },
                { 0.105f, 0.639f, 0.0f },
                { 0.070f, 0.604f, 0.0f },
                { 0.1025f, 0.613f, 0.0f },
            }
        },
        {
            {
                { -0.240f, -0.096f, 0.0f },
                { -0.073f, -0.217f, 0.0f },
                { -0.272f, -0.141f, 0.0f },
                { -0.080f, -0.307f, 0.0f }
            }
        },
        {
            {
                { -0.275f, 0.035f, 0.0f },
                { -0.243f, 0.038f, 0.0f },
                { -0.259f, -0.141f, 0.0f },
                { -0.204f, -0.141f, 0.0f }
            }
        },
        {
            {
                { -0.390f, -0.089f, 0.0f },
                { -0.399f, -0.141f, 0.0f },
                { -0.259f, -0.112f, 0.0f },
                { -0.220f, -0.179f, 0.0f },
                

            }
        },
        {
            {
                { -0.377f, -0.094f, 0.0f },
                { -0.514f, -0.058f, 0.0f },
                { -0.514f, -0.112f, 0.0f },
                { -0.546f, -0.064f, 0.0f }
            }
        },
        {
            {
                { -0.511f, -0.058f, 0.0f },
                { -0.578f, 0.045f, 0.0f },
                { -0.544f, -0.067f, 0.0f },
                { -0.604f, 0.045f, 0.0f },
            }
        },
        {
            {
                { -0.601f, 0.062f, 0.0f },
                { -0.581f, 0.058f, 0.0f },
                { -0.604f, 0.042f, 0.0f },
                { -0.575f, 0.042f, 0.0f }
            }
        },
        {
            {
                { -0.581f, 0.083f, 0.0f },
                { -0.581f, 0.083f, 0.0f },
                { -0.601f, 0.061f, 0.0f },
                { -0.578f, 0.058f, 0.0f }
            }
        },
        {
            {
                { -0.391f, -0.087f, 0.0f },
                { -0.597f, -0.109f, 0.0f },
                { -0.379f, -0.14f, 0.0f },
                { -0.585f, -0.141f, 0.0f }
            }
        },
        {
            {
                { -0.748f, -0.086f, 0.0f },
                { -0.598f, -0.105f, 0.0f },
                { -0.764f, -0.109f, 0.0f },
                { -0.584f, -0.14f, 0.0f }
            }
        },
        {
            {
                { -0.762f, -0.109f, 0.0f },
                { -0.744f, -0.086f, 0.0f },
                { -0.796f, -0.058f, 0.0f },
                { -0.773f, -0.058f, 0.0f }
            }
        },
        {
            {
                { -0.796f, -0.058f, 0.0f },
                { -0.783f, -0.013f, 0.0f },
                { -0.776f, -0.058f, 0.0f },
                { -0.780f, -0.010f, 0.0f },
            }
        },
        {
            {
                { -0.546f, -0.010f, 0.0f },
                { -0.748f, 0.013f, 0.0f },
                { -0.518f, -0.058f, 0.0f },
                { -0.748f, -0.016f, 0.0f },
                
            }
        },
        {
            {
                { -0.748f, -0.013f, 0.0f },
                { -0.776f, 0.086f, 0.0f },
                { -0.728f, 0.003f, 0.0f },
                { -0.774f, 0.137f, 0.0f },
                
            }
        },
        {
            {
                { -0.204f, 0.144f, 0.0f },
                { -0.233f, 0.109f, 0.0f },
                { -0.061f, 0.061f, 0.0f },
                { -0.067f, -0.035f, 0.0f }
            }
        },
        {
            {
                { -0.217f, 0.281f, 0.0f },
                { -0.176f, 0.262f, 0.0f },
                { -0.204f, 0.147f, 0.0f },
                { -0.157f, 0.099f, 0.0f }
            }
        }, 
        {
            {
                { -0.246f, 0.086f, 0.0f },
                { -0.348f, 0.278f, 0.0f },
                { -0.179f, 0.121f, 0.0f },
                { -0.323f, 0.297f, 0.0f }
            }
        }, 
        {
            {
                { -0.208f, 0.128f, 0.0f },
                { -0.438f, 0.137f, 0.0f },
                { -0.181f, 0.073f, 0.0f },
                { -0.454f, 0.112f, 0.0f }
            }
        },
        {
            {
                { -0.470f, 0.169f, 0.0f },
                { -0.447f, 0.240f, 0.0f },
                { -0.450f, 0.160f, 0.0f },
                { -0.425f, 0.224f, 0.0f },
                
            }
        },
        {
            {
                { -0.463f, 0.195f, 0.0f },
                { -0.466f, 0.173f, 0.0f },
                { -0.527f, 0.224f, 0.0f },
                { -0.546f, 0.208f, 0.0f },
                
            }
        },
        {
            {
                { -0.367f, 0.291f, 0.0f },
                { -0.489f, 0.390f, 0.0f },
                { -0.329f, 0.291f, 0.0f },
                { -0.460f, 0.419f, 0.0f }
            }
        },
        {
            {
                { -0.487f, 0.386f, 0.0f },
                { -0.508f, 0.473f, 0.0f },
                { -0.46f, 0.415f, 0.0f },
                { -0.495f, 0.498f, 0.0f }
            }
        },
        {
            {
                { -0.444f, 0.390f, 0.0f },
                { -0.431f, 0.431f, 0.0f },
                { -0.409f, 0.37f, 0.0f },
                { -0.415f, 0.431f, 0.0f }
            }
        },
        {
            {
                { -0.045f, 0.198f, 0.0f },
                { -0.182f, 0.326f, 0.0f },
                { -0.045f, 0.278f, 0.0f },
                { -0.166f, 0.371f, 0.0f }
            }
        },
        {
            {
                { -0.201f, 0.332f, 0.0f },
                { -0.233f, 0.518f, 0.0f },
                { -0.150f, 0.313f, 0.0f },
                { -0.204f, 0.514f, 0.0f }
            }
        },
        {
            {
                { -0.160f, 0.316f, 0.0f },
                { -0.310f, 0.367f, 0.0f },
                { -0.169f, 0.367f, 0.0f },
                { -0.300f, 0.393f, 0.0f },
            }
        },
        {
            {
                { -0.312f, 0.371f, 0.0f },
                { -0.364f, 0.508f, 0.0f },
                { -0.278f, 0.37f, 0.0f },
                { -0.348f, 0.518f, 0.0f }
            }
        },
        {
            {
                { -0.300f, 0.399f, 0.0f },
                { -0.345f, 0.390f, 0.0f },
                { -0.284f, 0.365f, 0.0f },
                { -0.339f, 0.371f, 0.0f }
            }
        },
        {
            {
                { -0.204f, 0.476f, 0.0f },
                { -0.166f, 0.527f, 0.0f },
                { -0.195f, 0.447f, 0.0f },
                { -0.144f, 0.534f, 0.0f }
            }
        },
        {
            {
                { -0.163f, 0.530f, 0.0f },
                { -0.144f, 0.530f, 0.0f },
                { -0.160f, 0.575f, 0.0f },
                { -0.141f, 0.565f, 0.0f }
            }
        },
        {
            {
                { -0.029f, 0.450f, 0.0f },
                { -0.086f, 0.518f, 0.0f },
                { -0.016f, 0.511f, 0.0f },
                { -0.051f, 0.543f, 0.0f },
                
            }
        },
        {
            {
                { -0.073f, 0.511f, 0.0f },
                { -0.067f, 0.537f, 0.0f },
                { -0.109f, 0.543f, 0.0f },
                { -0.102f, 0.553f, 0.0f }
            }
        },
        {
            {
                { -0.067f, 0.527f, 0.0f },
                { -0.048f, 0.543f, 0.0f },
                { -0.083f, 0.575f, 0.0f },
                { -0.077f, 0.581f, 0.0f }
            }
        }
    },
    {
        {
            {{ 0.01f, 0.77f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ 0.105f, 0.693f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ -0.553f, -0.109f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -10
        },
        {
            {{ -0.109f, 0.115f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -5
        },
        {
            {{ -0.058f, 0.173f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ 0.045f, 0.342f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ 0.051f, 0.444f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            0
        },
        {
            {{ -0.150f, 0.502f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ -0.815f, 0.064f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ 0.313f, 0.236f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ -0.048f, 0.668f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ 0.224f, 0.534f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ 0.323f, 0.505f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ 0.348f, 0.131f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ 0.626f, -0.019f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ -0.514f, 0.300f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ -0.578f, 0.348f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ -0.553f, 0.450f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ -0.284f, 0.297f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ -0.537f, 0.093f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ 0.572f, -0.233f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK,
            -20
        },
        {
            {{ 0.073f, -0.032f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -20
        },
        {
            {{ -0.14f, 0.639f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.109f, 0.565f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK_LIGHTER, 
            -10
        },
        {
            {{ 0.326f, 0.425f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK_LIGHTER, 
            -10
        },
        {
            {{ -0.479f, 0.144f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK_LIGHTER, 
            -10
        },
        {
            {{ 0.479f, -0.214f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.527f, 0.252f, 0.0f }, 0.023f, BLOOM_COLOR_LIGHT_PINK, 10},
            BLOOM_COLOR_LIGHT_PINK, 
            -10
        },
        {
            {{ 0.332f, -0.259f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.256f, 0.642f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.153f, 0.450f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ 0.540f, 0.374f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ 0.438f, 0.188f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            10
        },
        {
            {{ 0.387f, 0.284f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ 0.415f, 0.042f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ 0.220f, 0.042f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.629f, -0.211f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.707f, 0.022f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ 0.409f, -0.077f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.457f, 0.048f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.399f, 0.185f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            10
        },
        {
            {{ -0.288f, 0.042f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.169f, 0.294f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.268f, 0.419f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.016f, 0.591f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.275f, 0.380f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_WHITE, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.236f, 0.636f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.367f, 0.534f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.358f, 0.387f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.367f, 0.284f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.454f, 0.342f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.540f, 0.390f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.607f, 0.179f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.581f, -0.003f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -5
        },
        {
            {{ 0.482f, -0.105f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.805f, -0.179f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.690f, -0.13f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.665f, 0.022f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.556f, 0.163f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.671f, 0.153f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.482f, 0.310f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.454f, 0.454f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.029f, 0.240f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.195f, 0.335f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.345f, 0.112f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.498f, -0.217f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.812f, -0.182f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.116f, 0.256f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_BACK, 10},
            BLOOM_COLOR_DARK,
            -2
        },
        {
            {{ -0.760f, -0.153f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.645f, -0.080f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.058f, 0.348f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.268f, 0.176f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ 0.147f, 0.010f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.585f, -0.077f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ 0.562f, 0.006f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.633f, 0.112f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.249f, 0.543f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_YELLOW, 10},
            BLOOM_COLOR_DARK, 
            0
        },
        {
            {{ -0.054f, 0.438f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ -0.137f, 0.406f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.435f, 0.460f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.722f, 0.115f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTER, 10},
            BLOOM_COLOR_DARK, 
            -10
        },
        {
            {{ -0.377f, -0.064f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTEST, 10},
            BLOOM_COLOR_DARK, 
            -20
        },
        {
            {{ 0.249f, 0.160f, 0.0f }, BLOOM_RADIUS, BLOOM_COLOR_DARK_LIGHTEST, 10},
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

    

    return triangles;
}

std::vector<Triangle> creatBloomsSeperately(Tree& tree) {
    std::vector<Triangle> triangles;

    //for (auto& bloom : tree.blooms) {
    Bloom bloom = tree.blooms[30];
        std::vector<Triangle> bloomTriangles = createBloom(bloom.cirecleData.center, bloom.cirecleData.radius, bloom.cirecleData.color, bloom.centerColor, bloom.cirecleData.numTriangles, bloom.rotation, bloom.dynamicRotation);
        triangles.insert(triangles.end(), bloomTriangles.begin(), bloomTriangles.end());
    //}

    return triangles;
}


std::vector<Triangle> createBloom(
    GLfloat* center, 
    GLfloat radius, 
    GLfloat* color, 
    GLfloat* centerColor, 
    int numTriangles, 
    GLfloat staticRotation, 
    GLfloat dynamicRotation
) {
    std::vector<Triangle> triangles;

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

        // Apply static rotation
        Triangle::rotatePoint(petalCenter[0], petalCenter[1], center[0], center[1], staticRotation);

        // Apply dynamic rotation around the bloom's center
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(center[0], center[1], center[2])); // Translate to center
        transform = glm::rotate(transform, dynamicRotation, glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation
        transform = glm::translate(transform, -glm::vec3(center[0], center[1], center[2])); // Translate back

        glm::vec4 petalCenterVec = transform * glm::vec4(petalCenter[0], petalCenter[1], petalCenter[2], 1.0f);

        // Create petal
        auto petal = Triangle::createCircle(glm::value_ptr(petalCenterVec), radius, color, numTriangles);
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