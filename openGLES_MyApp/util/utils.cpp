#include "utils.h"
GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void*data /* = nullptr */){
	GLuint object;
	glGenBuffers(1, &object);
	glBindBuffer(bufferType, object);
	glBufferData(bufferType, size, data, usage);
	glBindBuffer(bufferType, 0);
	return object;
}
GLuint CompileShader(GLenum shaderType, const char*shaderPath){
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0){
		printf("glCreateShader fail\n");
		return 0;
	}
	int nFileSize = 0;
	const char* shaderCode = (char*)LoadFileContent(shaderPath, nFileSize);
	if (shaderCode == nullptr){
		printf("load shader code from file : %s fail\n", shaderPath);
		glDeleteShader(shader);
		return 0;
	}
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE){
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log : %s \nshader code :\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}
	delete shaderCode;
	return shader;
}
unsigned char* DecodeBMP(unsigned char*bmpFileData, int&width, int&height) {
	if (0x4D42 == *((unsigned short*)bmpFileData)) {
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char*pixelData = bmpFileData + pixelDataOffset;
		for (int i = 0; i < width*height * 3; i += 3) {
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}
		return pixelData;
	}
	return nullptr;
}
GLuint CreateTexture2D(unsigned char*pixelData, int width, int height, GLenum type) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//该函数表示的是当所显示的纹理比加载进来的纹理大时，采用GL_LINEAR的方法来处理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//该函数表示的是当所显示的纹理比加载进来的纹理小时，采用GL_LINEAR的方法来处理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);//将像素数据上传到GPU上，　参数1为纹理目标；参数2为目标的层次，即目标的详细程度，一般情况采用0即可；参数3表示的是数据成分的个数，如果数据由RGB构成，则将该参数设置为3；参数4和5分别为创建纹理数据的长和宽；参数6为边框的值，一般也设为0；参数8为数据的通道格式；参数9为纹理的数据元素类型；参数10为纹理的数据内容。
    

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
GLuint CreateTexture2DFromBMP(const char*bmpPath) {
	int nFileSize = 0;
	unsigned char *bmpFileContent = LoadFileContent(bmpPath, nFileSize);
	if (bmpFileContent == nullptr) {
		return 0;
	}
	int bmpWidth = 0, bmpHeight = 0;
	unsigned char*pixelData = DecodeBMP(bmpFileContent, bmpWidth, bmpHeight);
	if (bmpWidth == 0) {
		return 0;
	}
	GLuint texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);
	delete bmpFileContent;
	return texture;
}
GLuint CreateProcedureTexture(int size) {
	unsigned char *imageData = new unsigned char[size*size * 4];
	float halfSize = (float)size / 2.0f;
	float maxDistance = sqrtf(halfSize*halfSize + halfSize*halfSize);
	float centerX = halfSize;
	float centerY = halfSize;
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			int currentPixelOffset = (x + y*size) * 4;
			imageData[currentPixelOffset] = 255;
			imageData[currentPixelOffset + 1] = 255;
			imageData[currentPixelOffset + 2] = 255;
			float deltaX = (float)x - centerX;
			float deltaY = (float)y - centerY;
			float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
			float alpha = powf(1.0f - (distance / maxDistance), 8.0f);
			alpha = alpha > 1.0f ? 1.0f : alpha;
			imageData[currentPixelOffset + 3] = (unsigned char)(alpha*255.0f);
		}
	}
	GLuint texture = CreateTexture2D(imageData, size, size, GL_RGBA);
	delete imageData;
	return texture;
}

GLint CreateProgram(GLuint vsShader, GLuint fsShader) {
   GLint mProgram = glCreateProgram();
    glAttachShader(mProgram, vsShader);
    glAttachShader(mProgram, fsShader);
    glLinkProgram(mProgram);
    glDetachShader(mProgram, vsShader);
    glDetachShader(mProgram, fsShader);
    GLint nResult;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &nResult);
    if (nResult == GL_FALSE){
        char log[1024] = {0};
        GLsizei writed = 0;
        glGetProgramInfoLog(mProgram, 1024, &writed, log);
        printf("create gpu program fail,link error : %s\n", log);
        glDeleteProgram(mProgram);
        mProgram = 0;
        return 0;
    }
    return mProgram;
}
