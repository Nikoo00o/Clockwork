#version 330 core

layout (location = 0) in vec3 vertexPos;//3d position at first pos

uniform mat4 u_model;//model matrix with scaling/translation/rotation | position of the model in the world, etc with scaling 
uniform mat4 u_view;//view matrix is the world relative to the camera
uniform mat4 u_projection;//projection matrix for the viewport

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(vertexPos, 1.0);//calculate opengl position with the model, modelmatrix and then the projection matrix
}