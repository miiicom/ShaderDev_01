#version 430

out vec4 daColor;
in vec3 theNormal;
in vec3 thePosition;
in vec3 fragColor;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPosition;

void main()
{
	vec3 lightVector = normalize(pointLightPosition - thePosition);
	float Intensity = dot(lightVector,theNormal);
	daColor = vec4(Intensity,Intensity,Intensity,1.0);
}