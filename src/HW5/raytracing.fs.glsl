/**
 * a basic raytracer implementation
 */
#version 330 core

precision mediump float;


// input from vertex shader
//output of this shader
in vec3 upOffset;
in vec3 rightOffset;
in vec3 rayOrigin;
in vec3 rayDir;


// lights
uniform vec3 lightPosition;
//uniform vec3 lightColors[4];

// maximum ray depth
uniform int maxDepth;

uniform int noiseArea;


// CONSTANTS/DEFINE
#define INFINITY 100000.0
#define EPSILON 0.0000001
#define RAY_OFFSET 0.0001
#define MAX_DEPTH 3
#define USE_MultiSampling false
#define LIGHT_SIZE 0.1
#define SHADOW_SAMPLES 3 // attention! squared!!

// Function declarations
float intersectCylinder(vec3 origin, vec3 ray, vec3 base, float radius, float height);
vec3 normalForCylinder(vec3 hit, vec3 base, float radius);
void addCylinder(vec3 ro, vec3 rd, vec3 base, float radius, float height, vec3 color,
                 inout float hitDist, inout vec3 hitColor, inout vec3 hitNormal);
float noise(vec3 p);
vec3 applyNoiseTexture(vec3 position);
vec3 random3(vec3 c);


// SPHERE ----------------------------------------------------------------------
// ----------------------------------------------------------------------------
// The intersection function for a sphere 
float intersectSphere(vec3 origin, vec3 ray, vec3 sphereCenter, float sphereRadius) {
	vec3 toSphere = origin - sphereCenter;
	float a = dot(ray, ray);
	float b = 2.0 * dot(toSphere, ray);
	float c = dot(toSphere, toSphere) - sphereRadius*sphereRadius;
	float discriminant = b*b - 4.0*a*c;
	if(discriminant > 0.0) {
		float t = (-b - sqrt(discriminant)) / (2.0 * a);
		if(t > 0.0) { return t; }
	}
	return INFINITY ;
}

// ----------------------------------------------------------------------------
vec3 normalForSphere(vec3 hit, vec3 sphereCenter, float sphereRadius) {
	return (hit - sphereCenter) / sphereRadius;
}

// ----------------------------------------------------------------------------
void addSphere( vec3 ro, vec3 rd,
		vec3 center, float radius, vec3 color,
		inout float hitDist, inout vec3 hitColor, inout vec3 hitNormal ){

		float dist = intersectSphere(ro, rd, center, radius);

		if (dist < hitDist) {
				vec3 hit = ro + dist * rd;
				hitNormal = normalForSphere(hit, center, radius);
				hitColor = color;
				hitDist = dist;
			}
}

// PLANE -----------------------------------------------------------------------
// ----------------------------------------------------------------------------
float rayPlaneIntersection(vec3 rayStart, vec3 rayDir, vec4 plane, out vec3 hitColor)
{
	vec3 planeNormal = plane.xyz;
	float d = plane.w;
	float denom = dot(rayDir, planeNormal);
	if (abs(denom) < EPSILON) return INFINITY;
	float t = -(dot(rayStart, planeNormal) - d) / denom;
	if (t > 0.0) {
		// checkerboard color
		vec3 hitPos = rayStart + rayDir * t;
		float f = mod(floor(hitPos.z) + floor(hitPos.x), 2.0);
		hitColor = (f + 0.3) * vec3(0.5, 0.5, 0.5);
		return t;
	}
	else {
		return INFINITY;
	}
}
// ----------------------------------------------------------------------------
void addPlane(vec3 ro, vec3 rd, vec4 plane,
	inout float hitDist, inout vec3 hitColor, inout vec3 hitNormal) {
	vec3 planeColor = vec3(0.0);
	float dist = rayPlaneIntersection(ro, rd, plane, planeColor);
	if (dist < hitDist && dot(rd, -normalize(plane.xyz)) >= 0.0) {
		hitDist = dist;
		hitColor = planeColor;
		hitNormal = normalize(plane.xyz);
	}
}




// SCENE ------------------------------------------------------------------------
// scene descriptions
float rayTraceScene(vec3 ro, vec3 rd, out vec3 hitNormal, out vec3 hitColor) {
    float hitDist = INFINITY;
    hitNormal = vec3(0.0, 0.0, 0.0);

    // ground plane
    addPlane(ro, rd, vec4(0.0, 1.0, 0.0, 0.0), hitDist, hitColor, hitNormal);

    // spheres
    addSphere(ro, rd, vec3(1.0, 2.0, 5.0), 2.0, vec3(1.0, 0.0, 0.0), hitDist, hitColor, hitNormal);
    addSphere(ro, rd, vec3(5.0, 1.0, 2.0), 1.0, vec3(0.0, 1.0, 0.0), hitDist, hitColor, hitNormal);

    // new cylinder
    addCylinder(ro, rd, vec3(2.0, 0.0, 2.0), 1.0, 3.0, vec3(0.0, 1.0, 1.0), hitDist, hitColor, hitNormal);

    // apply noise texture based on the selected area
    if (hitDist < INFINITY) {
        if ((noiseArea == 0 && hitNormal.y == 1.0) ||  // Plane
            (noiseArea == 1 && length(hitNormal - normalForSphere(ro + rd * hitDist, vec3(1.0, 2.0, 5.0), 2.0)) < EPSILON) ||  // Sphere
            (noiseArea == 2 && length(hitNormal - normalForCylinder(ro + rd * hitDist, vec3(2.0, 0.0, 2.0), 1.0)) < EPSILON)) {  // Cylinder
            hitColor = applyNoiseTexture(ro + rd * hitDist);
        }
    }

    return hitDist;
}

// LIGHTING --------------------------------------------------------------------
// ----------------------------------------------------------------------------
float calcFresnel(vec3 normal, vec3 inRay) {
	float bias = 0.0; // higher means more reflectivity
	float cosTheta = clamp(dot(normal, -inRay), 0.0, 1.0);
	return clamp(bias + pow(1.0 - cosTheta, 2.0), 0.0, 1.0);
}

// ----------------------------------------------------------------------------
vec3 calcLighting(vec3 hitPoint, vec3 normal, vec3 inRay, vec3 color) {
	vec3 ambient = vec3(0.1);
	vec3 lightVec = lightPosition - hitPoint;
	vec3 lightDir = normalize(lightVec);
	float lightDist = length(lightVec);
	vec3 hitNormal, hitColor, shading=vec3(0.0);
	float shadowRayDist = rayTraceScene(hitPoint + lightDir*RAY_OFFSET, lightDir, hitNormal, hitColor );
	if(shadowRayDist < lightDist) {
		shading += ambient * color;
	} else {
		float diff = max(dot(normal, lightDir),0.0);
		vec3 h = normalize(-inRay + lightDir);
		float ndoth = max(dot(normal, h),0.0);
		float spec = max(pow(ndoth, 50.0),0.0);
		shading += min((ambient + vec3(diff)) * color + vec3(spec), 1.0);
	}
	return shading;
}
// ----------------------------------------------------------------------------
vec3 calcLightingSoftShadows(vec3 hitPoint, vec3 normal, vec3 inRay, vec3 color) {
  vec3 shading = vec3(0.0,0.0,0.0);

  float count = 0.0;
	vec3 ambient = vec3(0.1);
	const float delta = 2.0 / float(SHADOW_SAMPLES-1);
	for(float x=-1.0; x<=1.0; x+=delta){
		for(float y=-1.0; y<=1.0; y+=delta){
			vec3 nLightPos = lightPosition + vec3(x*LIGHT_SIZE,0.0,y*LIGHT_SIZE);
			vec3 lightVec = nLightPos - hitPoint;
			vec3 lightDir = normalize(lightVec);
			float lightDist = length(lightVec);
			vec3 hitNormal, hitColor;
			float shadowRayDist = rayTraceScene(hitPoint + lightDir*RAY_OFFSET, lightDir, hitNormal, hitColor );
			if(shadowRayDist < lightDist) {
				shading += ambient * color;
			} else {
				float diff = max(dot(normal, lightDir),0.0);
				vec3 h = normalize(-inRay + lightDir);
				float ndoth = max(dot(normal, h),0.0);
				float spec = max(pow(ndoth, 50.0),0.0);
				shading += min((ambient + vec3(diff)) * color + vec3(spec), 1.0);//diff*color * vec3(spec);
			}
			count += 1.0;
		}
	}
	return shading / count;
}


// ----------------------------------------------------------------------------
// shoot our ray into the scene:
void main() {
	gl_FragColor.rgba = vec4(0.0, 0.0, 0.0, 1.0);
	vec3 rayStart = rayOrigin;
	vec3 rayDirection = normalize(rayDir);

	vec3 hitColor = vec3( 0.0 );
	vec3 color = vec3(0.0);
	vec3 hitNormal;
	//float dist = rayTraceScene(rayStart, rayDirection, hitNormal, hitColor);
	float hits = 0.0;
	float totalDist = 0.0;

	for (int i = 0; i < maxDepth; i++)
	{
		float dist = rayTraceScene(rayStart, rayDirection, hitNormal, hitColor);
		if (dist >= INFINITY) {
			break;
		}
		float fresnel = calcFresnel(hitNormal, rayDirection);
		float weight = (1.0-fresnel)*(1.0-hits);
		hits += weight; 
		vec3 nearestHit = rayStart + dist * rayDirection;
		color.rgb += calcLighting(nearestHit, hitNormal, rayDirection, hitColor) * weight;

		rayDirection = reflect(rayDirection, hitNormal);
		rayDirection = normalize(rayDirection);
		rayStart = nearestHit + hitNormal * RAY_OFFSET;

	}
	
	if (hits > 0.0) color /= hits;
	gl_FragColor.rgb = vec3(color);
}

// GLSL function to generate noise
float noise(vec3 p) {
    vec3 i = floor(p);
    vec3 f = fract(p);
    f = f*f*(3.0-2.0*f);
    return mix(mix(mix(dot(random3(i), f - vec3(0,0,0)),
                       dot(random3(i + vec3(1,0,0)), f - vec3(1,0,0)), f.x),
                   mix(dot(random3(i + vec3(0,1,0)), f - vec3(0,1,0)),
                       dot(random3(i + vec3(1,1,0)), f - vec3(1,1,0)), f.x), f.y),
               mix(mix(dot(random3(i + vec3(0,0,1)), f - vec3(0,0,1)),
                       dot(random3(i + vec3(1,0,1)), f - vec3(1,0,1)), f.x),
                   mix(dot(random3(i + vec3(0,1,1)), f - vec3(0,1,1)),
                       dot(random3(i + vec3(1,1,1)), f - vec3(1,1,1)), f.x), f.y), f.z);
}

// Apply noise texture to a surface
vec3 applyNoiseTexture(vec3 position) {
    float n = noise(position * 10.0);
    return vec3(n, n, n);
}

// Intersection test for a cylinder
float intersectCylinder(vec3 origin, vec3 ray, vec3 base, float radius, float height) {
    vec3 d = ray;
    vec3 o = origin - base;
    float a = d.x * d.x + d.z * d.z;
    float b = 2.0 * (o.x * d.x + o.z * d.z);
    float c = o.x * o.x + o.z * o.z - radius * radius;
    float discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) return INFINITY;
    float t0 = (-b - sqrt(discriminant)) / (2.0 * a);
    float t1 = (-b + sqrt(discriminant)) / (2.0 * a);
    float t = min(t0, t1);
    float y = o.y + t * d.y;
    if (y < 0.0 || y > height) return INFINITY;
    return t;
}

// Intersection test for cylinder caps
float intersectCylinderCap(vec3 origin, vec3 ray, vec3 base, float radius, float height, bool top) {
    float t = (top ? (base.y + height - origin.y) : (base.y - origin.y)) / ray.y;
    if (t < 0.0) return INFINITY;
    vec3 hit = origin + t * ray;
    if (length(hit.xz - base.xz) > radius) return INFINITY;
    return t;
}

// Normal calculation for a cylinder
vec3 normalForCylinder(vec3 hit, vec3 base, float radius) {
    vec3 n = hit - base;
    n.y = 0.0;
    return normalize(n);
}

// Adding a cylinder to the scene
void addCylinder(vec3 ro, vec3 rd, vec3 base, float radius, float height, vec3 color,
                 inout float hitDist, inout vec3 hitColor, inout vec3 hitNormal) {
    float dist = intersectCylinder(ro, rd, base, radius, height);
    if (dist < hitDist) {
        vec3 hit = ro + dist * rd;
        hitNormal = normalForCylinder(hit, base, radius);
        hitColor = color;
        hitDist = dist;
    }
    float distBottom = intersectCylinderCap(ro, rd, base, radius, height, false);
    if (distBottom < hitDist) {
        vec3 hit = ro + distBottom * rd;
        hitNormal = vec3(0.0, -1.0, 0.0);
        hitColor = color;
        hitDist = distBottom;
    }
    float distTop = intersectCylinderCap(ro, rd, base, radius, height, true);
    if (distTop < hitDist) {
        vec3 hit = ro + distTop * rd;
        hitNormal = vec3(0.0, 1.0, 0.0);
        hitColor = color;
        hitDist = distTop;
    }
}

// GLSL function to generate random values
vec3 random3(vec3 c) {
    float j = 4096.0 * sin(dot(c, vec3(17.0, 59.4, 15.0)));
    vec3 r;
    r.z = fract(512.0 * j);
    j *= .125;
    r.x = fract(512.0 * j);
    j *= .125;
    r.y = fract(512.0 * j);
    return r - 0.5;
}