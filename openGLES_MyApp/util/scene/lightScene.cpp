//
//  lightScene.cpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/8/10.
//  Copyright © 2018年 58. All rights reserved.
//

#include "lightScene.hpp"
#include "utils.h"
#include "model.h"
#include "FrameBufferObject.hpp"
#include "fullscreenquad.hpp"
glm::mat4 viewMatrixL,projectionMatrixL;
glm::vec3 cameraPosL(4.0f,3.0f,4.0f);
Model modelL;
FrameBufferObject* fboL;
FullScreenQuad* fsqL;
void InitLight(){
    modelL.Init("Sphere.obj");
    modelL.mShader->Init("point_light.vs", "point_light.fs");
    modelL.SetPosition(0.0f, 0.0f, 0.0f);
    modelL.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
    modelL.mShader->SetVec4("U_AmbientLight", 0.1f, 0.1f, 0.1f, 1.0f);
    modelL.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
    modelL.mShader->SetVec4("U_DiffuseLight", 0.8f, 0.8f, 0.8f, 1.0f);//光源漫反射光的分量
    modelL.mShader->SetVec4("U_LightPos", 0.0f, 3.0f, 1.0f, 0.0f);
    modelL.mShader->SetVec4("U_SpecularLight", 1.0f, 1.0f, 1.0f, 1.0f);
    modelL.mShader->SetVec4("U_CameraPos", cameraPosL.x, cameraPosL.y, cameraPosL.z, 1.0f);
    viewMatrixL = glm::lookAt(cameraPosL, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
}
void SetViewPortSizeLight(float width,float height){
    projectionMatrixL = glm::perspective(50.0f, width/height, 0.1f, 100.f);
}
void DrawLight(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    modelL.Draw(cameraPosL.x, cameraPosL.y, cameraPosL.z, viewMatrixL, projectionMatrixL);
}
