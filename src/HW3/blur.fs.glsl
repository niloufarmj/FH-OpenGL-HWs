#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform vec2 pixelSize;
uniform sampler2D image;
uniform bool horizontal;

void main()
{
    vec2 pos = TexCoords;
    
    // Gaussian weights
    float values[9];
    values[0] = 0.05;
    values[1] = 0.09;
    values[2] = 0.11;
    values[3] = 0.15;
    values[4] = 0.2;
    values[5] = 0.15;
    values[6] = 0.11;
    values[7] = 0.09;
    values[8] = 0.05;

    vec3 result = vec3(0.0);
    if (horizontal)
    {
        vec2 curSamplePos = vec2(pos.x - 4.0 * pixelSize.x, pos.y);
        for (int i = 0; i < 9; i++)
        {
            result += texture(image, curSamplePos).rgb * values[i];
            curSamplePos.x += pixelSize.x;
        }
    }
    else
    {
        vec2 curSamplePos = vec2(pos.x, pos.y - 4.0 * pixelSize.y);
        for (int i = 0; i < 9; i++)
        {
            result += texture(image, curSamplePos).rgb * values[i];
            curSamplePos.y += pixelSize.y;
        }
    }
    FragColor = vec4(result, 1.0);
}