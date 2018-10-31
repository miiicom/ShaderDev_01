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
	daColor = vec4(Intensity + fragColor.x * ambientLightUniform.x,Intensity + fragColor.y * ambientLightUniform.y,Intensity + fragColor.z * ambientLightUniform.z,1.0);
}