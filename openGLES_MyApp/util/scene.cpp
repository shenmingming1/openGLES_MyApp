#include "scene.h"
#include "utils.h"

#include "skybox.h"
#include "ground.hpp"
//#include "vertexbuffer.h"
#include "shader.h"
#include "model.h"
//#include "particlesystem.h"

GLuint vbo,ebo,fsqVBO;
GLuint program;
GLuint texture;
GLint texcoordLocation,textureLocation;
GLint positionLocation,modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation,colorLocation;
GLuint colorBuffer,fbo;
VertexBuffer* vertextBuffer;
Shader* shader;
glm::mat4 projectionMatrix, viewMatrix,modelMatrix;
Ground ground;
Model model,niutou;
glm::vec3 cameraPos(20.0f,20.0f,20.0f);
SkyBox skybox;

// FBO逻辑处理器，不实际存储东西
void InitFBO(){
    GLint prevFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFBO);//获取当前绑定的FBO的值
    glGenFramebuffers(1,&fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 750.0, 1334.0, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);//可以将ColorBuffer绑定到一张Texture上。当然也可以绑定到多张贴图中。另外使用这个函数也可以取出深度贴图。
    //depth & stencil buffer
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindTexture(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, 750.0, 1334.0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
    int code = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (GL_FRAMEBUFFER_COMPLETE!=code) {
        printf("create fbo fail\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
}

void Init() {
    viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f,10.0f,0.0f), glm::vec3(0.0,1.0f,0.0f));//glm::mat4 mat = glm::LookAt(CameraPos, CameraTarget, upVector);cameraPos,相机的位置，CameraTarget相机看向的方向，相机头的朝向

    skybox.Init("Res");
    ground.Init();
    model.Init("Sphere.obj");
    model.SetPosition(0.0, 5.0, 0.0f);
//    model.mModelMatrix=glm::translate(0.0f, 20.0f, 0.0f)*glm::rotate(180.0f, 0.0f, 1.0f, 0.0f);
    model.SetTexture("earth.bmp");
    niutou.Init("niutou.obj");
    niutou.mModelMatrix=glm::translate(-5.0f, 0.0f, 4.0f)*glm::scale(0.05f, 0.05f, 0.05f);
    niutou.SetTexture("niutou.bmp");
    
    float fsqData[]{
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.5f,0.5f,0.0f,
        
//        -0.5f,-0.5f,0.0f,
//        0.5f, 0.5f,0.0f,
        -0.5f,0.5f,0.0f,
    };
    
//    Vertex vertex;
//    memset(&vertex, 0, sizeof(Vertex));
    fsqVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(float)*12, GL_STATIC_DRAW,&fsqData);
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, "fsq.vs");
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, "texture.fs");
    program = CreateProgram(vsShader, fsShader);
    positionLocation = glGetAttribLocation(program, "position");
    textureLocation = glGetUniformLocation(program, "U_MainTexture");
    modelMatrixLocation = glGetUniformLocation(program, "ModelMatrix");
    modelMatrix =glm::scale(0.5f, 0.5f, 0.5f);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    InitFBO();
/*使用vertexBuffer画三角形
    vertextBuffer = new VertexBuffer;
    vertextBuffer-> SetSize(4);
    vertextBuffer->SetPosition(0, -0.2f, -0.2f, 0.0f);
    vertextBuffer->SetTexcoord(0, 0.0f, 0.0f);
    vertextBuffer->SetColor(0, 1.0f, 1.0f, 1.0f);
    vertextBuffer->SetPosition(1, 0.2f, -0.2f, 0.0f);
    vertextBuffer->SetTexcoord(1, 1.0f, 0.0f);
    vertextBuffer->SetColor(1, 0.0f, 1.0f, 0.0f);
    vertextBuffer->SetPosition(2, -0.2f, 0.2f, 0.0f);
    vertextBuffer->SetTexcoord(2, 0.0f, 1.0f);
    vertextBuffer->SetColor(2, 1.0f, 1.0f, 1.0f);
    vertextBuffer->SetPosition(3, 0.2f, 0.2f, 0.0f);
    vertextBuffer->SetTexcoord(3, 1.0f, 1.0f);
    vertextBuffer->SetColor(3, 1.0f, 0.0f, 0.0f);
    shader = new Shader;
    shader->Init("test.vs", "test.fs");
    shader->SetTexture("U_Texture", "test.bmp");
    shader->SetTexture("U_Texture2", "niutou.bmp");
   */
    
    /*最初画三角形
    float data[] = {
        -0.2f,-0.2f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,
        0.2f,-0.2f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
        -0.2f,0.2f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,
        0.2f,0.2f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*40, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unsigned short indexes[]={0,1,2,3};
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*4, indexes, GL_STATIC_DRAW);
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
    viewMatrix = glm::rotate(60.0, 0.0, 0.0, 1.0);
    scale(0 .5,0.5 , 1.0);
    texture = CreateTexture2DFromBMP("test.bmp");
  */

} 
void SetViewPortSize(float width, float height) {
	projectionMatrix = glm::perspective(60.0f, width / height, 0.1f, 1000.0f);
    // 60.0f 为视角  0.1f,最近看到的距离，1000.0f最远看到的距离
}
void Draw() {
    GLint prevFBO;
    glGetIntegerv(0X8CA6, &prevFBO);// FBO逻辑处理器，不实际存储东西
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    skybox.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);
    ground.Draw(viewMatrix, projectionMatrix);
    model.Draw(cameraPos.x, cameraPos.y, cameraPos.y, viewMatrix, projectionMatrix);
    niutou.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);
 /*用vertextBuffer画三角形
    vertextBuffer->Bind();
    shader->Bind(glm::value_ptr(modelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glUniform1i(textureLocation, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    vertextBuffer->Unbind();
  */
    /* 

    float frameTime = GetFrameTime();
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));//1 为1个矩阵数组，GL_FALSE不需要转置 glm::value_ptr(modelMatrix)数据的起始地址
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float)*10, 0);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float)*10, (void*)(sizeof(float)*4));

    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation,2, GL_FLOAT, GL_FALSE, sizeof(float)*10, (void*)(sizeof(float)*8));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
    
	*/
    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
    glClearColor(0.1f, 0.4f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    skybox.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);
    ground.Draw(viewMatrix, projectionMatrix);
    model.Draw(cameraPos.x, cameraPos.y, cameraPos.y, viewMatrix, projectionMatrix);
    niutou.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glUniform1f(textureLocation, 0);
    glBindBuffer(GL_ARRAY_BUFFER, fsqVBO);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glUseProgram(0);
}

