#version 440

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexTexCoords;
layout(location = 3) in vec3 VertexTangent;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoords;
out mat3 TBNMatrix;

uniform mat4 VS_ModelMatrix;
uniform mat4 VS_ViewMatrix;
uniform mat4 VS_ProjectionMatrix;

void main()
{
	Position = vec4(VS_ModelMatrix * vec4(VertexPosition, 1.f)).xyz;
	Normal = mat3(VS_ModelMatrix) * normalize(VertexNormal);
	TexCoords = vec2(VertexTexCoords.x, VertexTexCoords.y  * -1.f); //Flip UVs

	vec3 N = mat3(VS_ModelMatrix) * normalize(VertexNormal);
	vec3 T = mat3(VS_ModelMatrix) * normalize(VertexTangent);
	vec3 B = cross(T, N);

	TBNMatrix = mat3(T, B, N);

	mat4 CombinedMatrix = VS_ProjectionMatrix * VS_ViewMatrix * VS_ModelMatrix;
	gl_Position = CombinedMatrix * vec4(VertexPosition, 1.f);
}