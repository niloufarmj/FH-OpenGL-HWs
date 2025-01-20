#version 460 core
precision highp float;

// input from vertex shader
in vec3 upOffset;
in vec3 rightOffset;
in vec3 rayOrigin;
in vec3 rayDir;

// output of this shader
out vec4 fragColor;

// uniforms
uniform vec3 lightPosition;
uniform float progress;  // the value of the slider in the menu
uniform float time; // time since GLFW was initialized in seconds

// CONSTANTS/DEFINE
const vec3 BACKGROUND = vec3(0.0, 0.0, 0.0);
const vec3 AMBIENT_COLOR = vec3(0.1, 0.1, 0.1);
const vec3 OBJECT_COLOR = vec3(0.7, 0.7, 0.7);

const float MAX_DIST = 100.0;
const vec4 MAX_DIST_DC = vec4(0.0, 0.0, 0.0, MAX_DIST);
const float EPSILON = 0.000125;
const float RAY_OFFSET = 0.1;
const float SHADOW_HARDNESS = 16.0;

const int STEP_LIMIT = 256;
const float STEP_EPSILON = 0.002;


vec3 displacement(in vec3 pos) {
    float waveX = sin(pos.y * 2.0 + time) * 0.1;
    float waveZ = cos(pos.x * 2.0 + time) * 0.1;
    return vec3(waveX, 0.0, waveZ);
}

// returns the distance-color vector that has the smaller distance value
vec4 minDCVec(vec4 a, vec4 b) {
    return vec4(mix(a.rgb, b.rgb, step(b.a, a.a)), min(a.a, b.a));
}

// applies a twist effect on the given position
vec3 twistPosition(in vec3 pos, in float k) {
    float c = cos(k * pos.y);
    float s = sin(k * pos.y);
    mat2  m = mat2(c, -s, s, c);
    vec3  q = vec3(m * pos.xz, pos.y);
    return q;
}

// combines the two objects at distances a and b (A | B)
float sdUnion(in float a, in float b) {
    return min(a, b);
}

// smoothly combines the two objects at distances a and b via a polynomial interpolation (A | B)
float sdSmoothUnion(in float a, in float b, in float k) {
    float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
    return mix(b, a, h) - k * h * (1.0 - h);
}

// intersects the object at distance a with the object at distance b (A & B)
float sdIntersection(in float a, in float b) {
    return max(a, b);
}

// smoothly intersects the object at distance a with the object at distance b (A & B)
float sdSmoothIntersection(in float a, in float b, in float k) {
    float h = clamp(0.5 - 0.5 * (b - a) / k, 0.0, 1.0);
    return mix(b, a, h) + k * h * (1.0 - h);
}

// substracts the object at distance b from the object at distance a (A - B)
float sdDifference(in float a, in float b) {
    return max(a, -b);
}

// smoothly substracts the object at distance b from the object at distance a (A - B)
float sdSmoothDifference(in float a, in float b, in float k) {
    float h = clamp(0.5 - 0.5 * (b + a) / k, 0.0, 1.0);
    return mix(b, -a, h) + k * h * (1.0 - h);
}

// a plane parallel to the XZ plane at the given height
float sdAAPlane(in vec3 pos, in float height) {
    return pos.y - height;
}

// a sphere of a given radius
float sdSphere(in vec3 pos, in  float radius) {
    return length(pos) - radius;
}

// an axis-aligned cube; radii are the side lengths in along each axis halfed
float sdAACube(in vec3 pos, in vec3 radii) {
    vec3 distances = abs(pos) - radii;
    return min(max(distances.x, max(distances.y, distances.z)), 0.0) + length(max(distances, 0.0));
}

// an axis-aligned torus; radii are outter (x) and inner (y) radius
float sdAATorus(in vec3 pos, in vec2 radii) {
    return length(vec2(length(pos.xy) - radii.x, pos.z)) - radii.y;
}

// a cylinder of the given radius spanning from the origin to the given end coordinate
float sdCylinder(in vec3 pos, in vec3 end, in float radius) {
    float eeDot = dot(end, end);
    float peDot = dot(pos, end);
    float x = length(pos * eeDot - end * peDot) - radius * eeDot;
    float y = abs(peDot - eeDot * 0.5) - eeDot * 0.5;
    float x2 = x * x;
    float y2 = y * y * eeDot;

    float d = (max(x, y) < 0.0) ? -min(x2, y2) : (((x > 0.0) ? x2 : 0.0) + ((y > 0.0) ? y2 : 0.0));

    return sign(d) * sqrt(abs(d)) / eeDot;
}

// a mug showcasing how primitves can be combined to produce something complex
float sdMug(in vec3 pos) {
    vec3 curPos;

    float distTorus = sdAATorus(pos - vec3(0.2, 0.0, 0.0), vec2(0.35, 0.0625));
    float distCube = sdAACube(pos - vec3(-0.25, 0.0, 0.0), vec3(0.45, 1.0, 1.0));
    float distHandle = sdDifference(distTorus, distCube);

    float distOutterCylinder = sdCylinder(pos - vec3(-0.25, -0.5, 0.0), vec3(0.0, 1.0, 0.0), 0.5) - 0.005;
    float distInnerCylinder = sdCylinder(pos - vec3(-0.25, -0.4375, 0.0), vec3(0.0, 1.0, 0.0), 0.40);
    float distContainer = sdDifference(distOutterCylinder, distInnerCylinder);

    return sdSmoothUnion(distHandle, distContainer, 0.05);
}

// an infinte grid of spheres of the given radius with the given spacing
float sdSphereGrid(in vec3 pos, in float radius, in float spacing) {
    vec3 relPos = pos - spacing * round(pos / spacing);
    return sdSphere(relPos, radius);
}

// an axis-aligned infinte grid of axis-aligned cubes of the given size with the given spacing
float sdAACubeGrid(in vec3 pos, in vec3 cubeSize, in float spacing) {
    vec3 relPos = pos - spacing * round(pos / spacing);
    return sdAACube(relPos, cubeSize);
}

// an axis-aligned megner cube fractal
float sdAAMengerCube(in vec3 pos, in float scale, in int iterations) {
    float dist = sdAACube(pos, vec3(scale));

    float s = 1.0;
    for (int m = 0; m < 3; ++m)
    {
        vec3 a = mod(pos * s * (1.0 / scale), 2.0) - 1.0;
        s *= 3.0;
        vec3 r = abs(1.0 - 3.0 * abs(a));

        float da = max(r.x, r.y);
        float db = max(r.y, r.z);
        float dc = max(r.z, r.x);
        float c = (min(da, min(db, dc)) - 1.0) / s;

        dist = max(dist, c);
    }

    return dist;
}

// CONE ------------------------------------------------------------------------
float sdCone(in vec3 pos, in float height, in float radius) {
    vec2 q = vec2(length(pos.xz), pos.y);
    vec2 tip = q - vec2(radius, height);
    vec2 mantleDir = normalize(vec2(radius, height));
    float mantle = dot(tip, mantleDir);
    float d = max(mantle, -q.y);
    return d;
}

// HOUSE -----------------------------------------------------------------------
float sdHouse(in vec3 pos, float progress) {
    // Adjust position to place the house on the plane
    pos.y += 0.5;
    
    // Apply a twist effect based on progress
    pos = twistPosition(pos, progress * 3.14);
    
    // Base of the house
    float baseHeight = 0.5 + 0.5 * progress; // Vary height with progress
    float base = sdAACube(pos, vec3(1.0, baseHeight, 1.0));
    
    // Roof of the house (pyramid)
    float roofHeight = 1.0 + progress; // Vary roof height with progress
    float roof = sdCone(pos - vec3(0.0, baseHeight, 0.0), roofHeight, 1.0);
    
    // Door of the house
    float door = sdAACube(pos - vec3(0.0, -0.25, 1.0), vec3(0.3, 0.5, 0.1));
    
    // Combine base and roof, and subtract the door
    float house = sdUnion(base, roof);
    house = sdDifference(house, door);
    
    return house;
}

// TREE ------------------------------------------------------------------------
float sdTree(in vec3 pos, float progress) {
    // Adjust position to place the tree on the plane
    pos.y += 0.5;
    
    // Apply a bending effect based on progress
    float bend = sin(progress * 3.14) * 0.5;
    pos.x += pos.y * bend;
    
    // Trunk of the tree
    float trunkHeight = 1.0 + progress; // Vary trunk height with progress
    float trunk = sdCylinder(pos, vec3(0.0, trunkHeight, 0.0), 0.2);
    
    // Foliage of the tree
    float foliageSize = 0.75 + 0.5 * progress; // Vary foliage size with progress
    float foliage = sdSphere(pos - vec3(0.0, trunkHeight + 0.5, 0.0), foliageSize);
    
    // Branches of the tree
    float branch1 = sdCylinder(pos - vec3(0.0, trunkHeight * 0.5, 0.0), vec3(1.0, 0.0, 0.0), 0.1);
    float branch2 = sdCylinder(pos - vec3(0.0, trunkHeight * 0.75, 0.0), vec3(-1.0, 0.0, 0.0), 0.1);
    
    // Combine trunk, foliage, and branches
    float tree = sdUnion(trunk, foliage);
    tree = sdUnion(tree, branch1);
    tree = sdUnion(tree, branch2);
    
    return tree;
}


// evaluate the distance field at the given position; maps a coordinate to a distance
// returns a vector containg RGB values and the distance
vec4 map(in vec3 pos) {
    vec4 result = MAX_DIST_DC;

    // Existing objects
    float distPlane = sdAAPlane(pos, -2.0);

    // New objects
    float distHouse = sdHouse(pos - vec3(2.0, 0.0, 0.0), progress/5);
    float distTree = sdTree(pos - vec3(-2.0, 0.0, 0.0), progress/5);
    vec4 dcHouse = vec4(vec3(0.6, 0.3, 0.2), distHouse);
    vec4 dcTree = vec4(vec3(0.0, 0.8, 0.0), distTree);

    // Assign colors to the distances
    vec3 planeColor = vec3(mod(floor(pos.z) + floor(pos.x), 2.0) * 0.7);
    vec4 dcPlane = vec4(planeColor.xyz, distPlane);

    // Combine all objects
    result = minDCVec(result, dcPlane);
    result = minDCVec(result, dcHouse);
    result = minDCVec(result, dcTree);

    return result;
}

// march through the distance field 
vec4 raymarch(inout vec3 pos, in vec3 raydir) {
    int step = 0;
    float totalDist = 0.0;
    vec4 curDC = map(pos);
    float curDist = curDC.a;
    while (curDist > STEP_EPSILON && totalDist < MAX_DIST && step < STEP_LIMIT) {
        pos = pos + raydir * curDist;
        pos += displacement(pos);  // Apply displacement
        totalDist += curDist;
        curDC = map(pos);
        curDist = curDC.a;
        ++step;
    }
    return (step < STEP_LIMIT) ? vec4(curDC.rgb, totalDist) : MAX_DIST_DC;
}

// evaluate the normal at a positon based on the local gradient of the signed distance field
vec3 getNormal(in vec3 pos) {
    float posDist = map(pos).a;
    float gradientX = map(vec3(pos.x + EPSILON, pos.y, pos.z)).a - posDist;
    float gradientY = map(vec3(pos.x, pos.y + EPSILON, pos.z)).a - posDist;
    float gradientZ = map(vec3(pos.x, pos.y, pos.z + EPSILON)).a - posDist;
    return normalize(vec3(gradientX, gradientY, gradientZ));
}

// returns 0 when the position lies within the shadow of an object; otherwise 1
float hardShadow(in vec3 pos) {
    vec3 lightDir = normalize(lightPosition - pos);
    float distLight = length(lightPosition - pos);

    float t = RAY_OFFSET;
    for (int step = 0; t < distLight && step < STEP_LIMIT; ++step) {
        float d = abs(map(pos + t * lightDir).a);
        if (d < STEP_EPSILON) {
            return 0.0f;
        }
        t += d;
    }
    return 1.0f;
}

// returns a percentage value describing how strongly illuminated the given position is
float softShadow(in vec3 pos) {
    vec3 lightDir = normalize(lightPosition - pos);
    float distLight = length(lightPosition - pos);

    float illumination = 1.0f;
    float t = RAY_OFFSET;
    for (int step = 0; t < distLight && step < STEP_LIMIT; ++step) {
        float d = abs(map(pos + t * lightDir).a);
        if (d < STEP_EPSILON) {
            return 0.0f;
        }
        illumination = min(illumination, SHADOW_HARDNESS * d / t);
        t += d;
    }
    return illumination;
}

// computes the lighting model for the given ray while applying the passed color
vec3 illuminate(in vec3 pos, in vec3 rayDir, in vec3 color) {
    vec3 normal = getNormal(pos);
    vec3 lightDir = normalize(lightPosition - pos);

    float diffuse = max(dot(lightDir, normal), 0.0);
    vec3 h = normalize(lightDir - rayDir);
    float rdoth = max(dot(normal, h), 0.0);
    float specular = pow(max(rdoth, 0.0), 50.0);

    float illumination = softShadow(pos); // alternatives: 1.0, hardShadow(pos)

    return (AMBIENT_COLOR + diffuse * illumination) * color + vec3(specular);
}


void main() {
    vec3 rayDirection = normalize(rayDir);
    vec3 color = BACKGROUND;
    vec3 pos = vec3(rayOrigin.xyz);

    vec4 dc = raymarch(pos, rayDirection);

    

    //// apply a lighting model 
    if (dc.a < MAX_DIST) {
        vec3 objColor = dc.rgb;
        color = illuminate(pos, rayDirection, objColor);
    }

    fragColor.rgb = color.rgb;
}
