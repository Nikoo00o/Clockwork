#version 330 core
  
in vec2 fragTexCoord;//get texture coordinates from vertex shader 
flat in int fragTexId;//also flat specifier for integer as input in the fragmentshader like the output in the vertexshader

out vec4 outColour;//output final colour 

uniform sampler2DArray u_texture1;//sampler(2d for 2dtexture) to access the textureobject in the fragment shader via an uniform |

void main()
{
    outColour = texture(u_texture1,vec3(fragTexCoord,fragTexId));//update colour by calculating it with texture(parameters uniform texture and the input texturecoords) and the input colour
	//glsls built in texture function takes in a texture sampler as its first argument and the corresponding texture coordinate as the second argument | the function samples the corresponding colour value using the texture parameters | the output colour of the fragment shader is the filtered colour of the texture at the interpolated texture coordinate 
}//here the input colour from the vertex array is also mixed with the texture colour | the two textures are also mixed together and the third parameter is between 0 and 1 for the mix ratio where 1 is the second argument and 0 is the first argument 