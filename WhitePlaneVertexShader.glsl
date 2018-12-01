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
uniform float time;
uniform vec2 SpriteOffset;
uniform sampler2D displaceTextureTC;

out vec3 LightDirectionTangentSpace;
out vec3 ViewDirectionTangentSpace;
out vec3 fragColor;
out vec2 fragmentUV0;

void main()
{	//sprite loc
	vec2 ShrinkFragUV0 = vec2(vertexUV0.x / 16,vertexUV0.y/ 16);
	vec2 MovedFragmentUV0 = ShrinkFragUV0 + SpriteOffset;
	vec4 texel = texture2D(displaceTextureTC, MovedFragmentUV0);
	vec4 vertexPositionOffsetted = vec4(vertexPositionModel.x,vertexPositionModel.y + (texel.x / 5),vertexPositionModel.z,vertexPositionModel.w);

	//gl_Position = modelToProjectionMatrix *  vertexPositionModel;
	gl_Position = modelToProjectionMatrix *  vertexPositionOffsetted;

	//Transform normal and tangent to eye space
	vec3 NormalView = normalize(vec3(modelToViewTransMatrix * vec4(normalModel,0.0)));
	vec3 TangentView = normalize(vec3(modelToViewTransMatrix * vec4(tangentModel,0.0)));
	//Calculate Binormal
	vec3 binormal = normalize(cross(NormalView,TangentView)) * 1 ; // 1 for handedness

	//Matrix for transformation to tangent space
	mat3 ViewToOBJTangentSpce  = mat3(
		TangentView.x, binormal.x, NormalView.x,
		TangentView.y, binormal.y, NormalView.y,
		TangentView.z, binormal.z, NormalView.z
	);

	//Get position in view coordinate
	vec3 PositionInView = vec3(modelToViewTransMatrix  * vertexPositionModel);
	vec4 pointLightPositionInView = normalize(WorldToViewMatrix * vec4(pointLightPosition,1.0));

	LightDirectionTangentSpace = normalize( ViewToOBJTangentSpce * (pointLightPositionInView.xyz - PositionInView));
	ViewDirectionTangentSpace = ViewToOBJTangentSpce * normalize(-PositionInView);

	fragColor = vertexColorModel.xyz;
	fragmentUV0 = vertexUV0;
}