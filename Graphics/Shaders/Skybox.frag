#version 460

in vec3 vertexOut;
out vec4 pixelColor;

uniform samplerCube skybox;

void main(void)
{
	pixelColor = texture(skybox, vertexOut);
}