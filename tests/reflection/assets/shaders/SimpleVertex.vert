#version 450

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iUV;

layout (location = 0) out vec4 oColor;

layout (binding = 0) uniform iMatrices
{
  mat4 mModel;
};

layout (binding = 0, std140) uniform UBO
{
  mat4 mView;
  mat4 mProj;
};



void main() {
  oColor = iColor;
  gl_Position = mModel * mView * mProj * vec4(iPos, 1.0f);
}
