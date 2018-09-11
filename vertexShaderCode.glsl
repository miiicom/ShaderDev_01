#version 430

in layout(location=0) vec2 position;
in layout(location=1) vec3 vertexColor;

uniform float xMove;
uniform float yMove;
uniform float Flip;

out vec3 theColor;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	gl_Position.x = gl_Position.x + xMove;
	gl_Position.y = gl_Position.y + yMove;
	gl_Position.y = gl_Position.y * Flip;
	theColor = vertexColor;
	theColor.x= xMove;
	theColor.y= yMove;
}