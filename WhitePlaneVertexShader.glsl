#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec4 vertexColorModel;
in layout(location=2) vec3 normalModel;
in layout(location=3) vec2 vertexUV0;
in layout(location=4) vec3 tangentModel;

uniform vec3 ambientLightUniform;
uniform vec3 pointLightPosition;
uniform mat4 modelToProjectionMatrix; //AKA MVP - Model to World->World to View->View To Projection
uniform mat4 modelToWorldTransMatrix;
uniform mat4 modelToViewTransMatrix;
uniform mat4 WorldToViewMatrix;
uniform mat3 idealMatrix;
uniform vec2 SpriteOffset;
uniform sampler2D displaceTextureTC;
uniform float time;

out mat3 TBNtangentToModel;
out vec3 vertexPositionWorld;
out vec3 fragColor;
out vec2 fragmentUV0;
out vec3 normalWorld;

void main()
{	//sprite loc
	vec2 ShrinkFragUV0 = vec2(vertexUV0.x / 16,vertexUV0.y/ 16);
	vec2 MovedFragmentUV0 = ShrinkFragUV0 + SpriteOffset;
	vec4 texel = texture2D(displaceTextureTC, MovedFragmentUV0);
	vec4 vertexPositionOffsetted = vec4(vertexPositionModel.x,vertexPositionModel.y + (texel.x /2.5),vertexPositionModel.z,vertexPositionModel.w);

	//gl_Position = modelToProjectionMatrix *  vertexPositionModel;

	gl_Position = modelToProjectionMatrix *  vertexPositionOffsetted;

	//Transform normal and tangent to world space and then calculate bitangent
	vec3 biTangentModel = normalize(cross(normalModel,tangentModel)) * 1 ;		//1 for handedness ion OpenGL 
		
	//Construct TBN Matrix
	TBNtangentToModel =  mat3(tangentModel,biTangentModel,normalModel);

	normalWorld = vec3(modelToWorldTransMatrix * vec4(normalModel, 0));
	vertexPositionWorld = vec3(modelToWorldTransMatrix * vertexPositionModel);
	fragColor = vertexColorModel.xyz;
	fragmentUV0 = MovedFragmentUV0;
}