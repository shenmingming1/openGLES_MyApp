#include "scene.h"
#include "utils.h"

//#include "skybox.h"
//#include "ground.h"
//#include "vertexbuffer.h"
//#include "shader.h"
//#include "model.h"
//#include "particlesystem.h"
GLuint vbo,ebo;
GLuint program;
GLuint texture;
GLint texcoordLocation,textureLocation;
GLint positionLocation,modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation,colorLocation;

glm::mat4 projectionMatrix, viewMatrix,modelMatrix;

void Init() {
    float data[] = {
        -0.2f,-0.2f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,
        0.2f,-0.2f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
        0.0f,0.2f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.5f,1.0f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*30, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unsigned short indexes[]={0,1,2};
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*3, indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    int fileSize = 0;
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, "test.vs");
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, "test.fs");
    program = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    positionLocation = glGetAttribLocation(program, "position");
    colorLocation = glGetAttribLocation(program, "color");
    texcoordLocation = glGetAttribLocation(program, "texcoord");
    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "ViewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "ProjectionMatrix");
    textureLocation = glGetUniformLocation(program, "U_Texture");
    modelMatrix = glm::translate(0.0f, 0.0f, -0.6f);
    texture = CreateTexture2DFromBMP("niutou.bmp");
} 
void SetViewPortSize(float width, float height) {
	projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
    // 60.0f 为视角  0.1f,最近看到的距离，1000.0f最远看到的距离
}
void Draw() {
    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    float frameTime = GetFrameTime();
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));//1 为1个矩阵数组，GL_FALSE不需要转置 glm::value_ptr(modelMatrix)数据的起始地址
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glBindBuffer(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float)*10, 0);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float)*10, (void*)(sizeof(float)*4)); 
    
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,2, GL_FLOAT, GL_FALSE, sizeof(float)*10, (void*)(sizeof(float)*8));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
	
}
