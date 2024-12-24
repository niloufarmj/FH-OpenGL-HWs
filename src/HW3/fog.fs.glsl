#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D scene;
uniform vec3 fogColor;
uniform float fogDensity;

void main()
{
    vec4 color = texture(scene, TexCoords);
    float depth = gl_FragCoord.z / gl_FragCoord.w;
    float fogFactor = exp(-fogDensity * depth);
    fogFactor = clamp(fogFactor, 0.0, 1.0);
    vec3 finalColor = mix(fogColor, color.rgb, fogFactor);
    FragColor = vec4(finalColor, color.a);
}