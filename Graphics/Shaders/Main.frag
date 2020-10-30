#version 460

in vec3 colorOut;
out vec4 pixelColor;

uniform float time;

void main(void)
{
	float factor = abs(sin(time));
	pixelColor = vec4(factor, factor, 0.0f, 1.0f); 
}