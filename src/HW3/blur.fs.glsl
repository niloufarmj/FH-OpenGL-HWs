#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D image;
uniform bool horizontal;

void main() {
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    vec3 result = vec3(0.0);
    float weight[5] = float;
    for (int i = -4; i < 5; ++i) {
        for (int j = -4; j < 5; ++j) {
            vec2 offset = horizontal ? vec2(tex_offset.x * float(i), 0.0) : vec2(0.0, tex_offset.y * float(j));
            result += texture(image, TexCoords + offset).rgb * weight[abs(i)];
        }
    }
    FragColor = vec4(result, 1.0);
}