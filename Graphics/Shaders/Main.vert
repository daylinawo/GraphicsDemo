#version 460

layout (location = 0) in vec3 vertexIn;
layout (location = 1) in vec4 colorIn;
layout (location = 2) in vec2 textureIn;
layout (location = 3) in vec3 normalIn;

out vec3 vertexOut;
out vec4 colorOut;
out vec2 textureOut;
out vec3 normalOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;


void main(void)
{
	//send interpolated color to fragment shader
	colorOut = colorIn;

	//send interpolated vertex position data to fragment shader (world space)
	vertexOut = (model * vec4(vertexIn, 1.0)).xyz;

	//send interpolated texture UV coordinate data to fragment shader
	textureOut = textureIn;

	//send interpolated normal to fragment shader (world space)
	normalOut = normal * normalIn;

	//interpolate each vertex based on MVP transformations
	gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}