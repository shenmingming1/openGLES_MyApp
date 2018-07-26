#pragma once
#include "ggl.h"
struct UniformVector4f{
	GLint mLocation;
	float v[4];
	UniformVector4f() {
		mLocation = -1;
		memset(v,0,sizeof(float)*4);
	}
};
struct UniformTexture{
	GLint mLocation;
	GLuint mTexture;
	UniformTexture() {
		mLocation = -1;
		mTexture = 0;
	}
};
class Shader {
protected:
	GLuint CompileShader(GLenum shaderType, const char*shaderCode);
	void CreateProgram(GLuint vsShader, GLuint fsShader);
public:
	GLuint mProgram;
	GLuint mPosition;
	GLuint mColor;
	GLuint mTexcoord;
	GLuint mNormal;
	GLint mModelMatrixLocation, mViewMatrixLocation, mProjectionMatrixLocation,mIT_ModelMatrix;
	GLint mPositionLocation, mColorLocation, mTexcoordLocation, mNormalLocation;
	std::map<std::string, UniformVector4f*> mUniformVec4s;
	std::map<std::string, UniformTexture*> mUniformTextures;
	void SetVec4(const char * name, float x, float y, float z, float w);
	void SetTexture(const char * name, const char*imagePath);
	void Init(const char*vs, const char*fs);
	void Bind(float *M,float *V,float*P);
};