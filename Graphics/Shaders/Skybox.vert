#version 460

layout (location = 0) in vec3 vertexIn;

out vec3 vertexOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	//send interpolated vertex position data to fragment shader (world space)
	vertexOut = (model * vec4(vertexIn, 1.0)).xyz;

	//interpolate each vertex based on MVP transformations
	gl_Position = projection * view * model * vec4(vertexIn, 1.0);
}