#pragma once
#include "vertexbuffer.hpp"
#include "shader.h"
class Model {
	VertexBuffer*mVertexBuffer;
public:
	Model();
    Shader*mShader;
	glm::mat4 mModelMatrix;
	void Init(const char*modelPath);
	void SetTexture(const char*imagePath);
	void SetPosition(float x, float y, float z);
	void Draw(float x, float y, float z, glm::mat4 & viewMatrix, glm::mat4 projectionMatrix);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
};
