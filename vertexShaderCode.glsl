#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentWorld;

out vec2 fragmentUV0;

void main()
{
	gl_Position =vertexPositionModel;
	fragmentUV0 = vertexUV0;
}