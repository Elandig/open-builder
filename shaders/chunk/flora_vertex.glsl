#version 330

layout (location = 0) in vec3 inVertexCoord;
layout (location = 1) in vec3 inTextureCoord;
layout (location = 2) in float inBasicLight;

uniform mat4 projectionViewMatrix;
uniform float time;

out vec3 passTexCoord;
out float passBasicLight;

vec4 waveLeaf()
{
    //Have to do this as in variables cannot be mutated
    vec3 position = inVertexCoord;
    position.y += sin((time + position.x) * 1.5) / 32.0f;
    position.x += cos((time + position.z) * 1.5) / 32.0f;
    position.z += sin((time + position.z) * 1.5) / 32.0f;
    return vec4(position, 1.0);
}

void main() {
    gl_Position = projectionViewMatrix * waveLeaf();
    
    passTexCoord = inTextureCoord;
    passBasicLight = inBasicLight;
}