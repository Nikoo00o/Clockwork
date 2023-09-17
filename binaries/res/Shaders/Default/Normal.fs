#version 330 core
  
in vec2 fragTexCoord;//get texture coordinates from vertex shader 

out vec4 outColour;//output final colour 

uniform sampler2D u_texture1;//sampler(2d for 2dtexture) to access the textureobject in the fragment shader via an uniform |

void main()
{
    outColour = texture(u_texture1, fragTexCoord);
}