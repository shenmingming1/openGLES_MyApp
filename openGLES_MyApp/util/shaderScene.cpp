//
//  shaderScene.cpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/8/9.
//  Copyright © 2018年 58. All rights reserved.
//

#include "shaderScene.hpp"
#include "utils.h"
#include "model.h"
#include "FrameBufferObject.hpp"
#include "fullscreenquad.hpp"
glm::mat4 viewMatrixS,projectionMatrixS;
glm::vec3 cameraPosS(4.0f,3.0f,4.0f);
Model modelS;
FrameBufferObject* fboS;
FullScreenQuad* fsqS;
void InitShaderScene(){
    modelS.Init("Sphere.obj");
    modelS.mShader->Init("rgbcube.vs", "rgbcube.fs");
    modelS.SetPosition(0.0f, 0.0f, 0.0f);
    viewMatrixS = glm::lookAt(cameraPosS, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    fsqS = new FullScreenQuad;
    fsqS->Init();
    fsqS->mShader->Init("fullscreenquad.vs", "gray.fs");
}
void SetViewPortSizeShaderScene(float width,float height){
    projectionMatrixS = glm::perspective(50.0f, width/height, 0.1f, 100.f);
    fboS = new FrameBufferObject;
    fboS->AttachColorBuffer("color", GL_COLOR_ATTACHMENT0, (int)width, (int)height);
    fboS->AttachDepthBuffer("depth", (int)width, (int)height);
    fboS->Finish();
    fsqS->mShader->SetTexture("U_Texture", fboS->GetBuffer("color"));
    fboS->Bind();
    modelS.Draw(cameraPosS.x, cameraPosS.y, cameraPosS.z, viewMatrixS,projectionMatrixS);
    fboS->UnBind();
}
void DrawShaderScene(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    fsqS->Draw();
    
}
