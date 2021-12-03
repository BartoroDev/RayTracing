#shader VERTEX
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
//layout(location = 1) in vec2 TexCoord;

out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * a_Position;
   v_Color = a_Color;
};

#shader FRAGMENT
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

//uniform sampler2D u_Texture;
//uniform vec4 u_Color;

void main()
{
	//vec4 TexColor = texture(u_Texture, v_TexCoord);
	color = v_Color;
};