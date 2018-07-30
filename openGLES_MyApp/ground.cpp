//
//  ground.cpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/7/25.
//  Copyright © 2018年 58. All rights reserved.
//

#include "ground.hpp"
void Ground::Init() {
    mVertexBuffer = new VertexBuffer;
    mVertexBuffer->SetSize(1600);
    for (int z = 0; z < 20; ++z) {
        float zStart = 100.0f - z*10.0f;
        for (int x = 0; x < 20; ++x) {
            int offset = (x + z * 20)*4;
            float xStart = x*10.0f - 100.0f;
            mVertexBuffer->SetPosition(offset, xStart, -1.0f, zStart);
            mVertexBuffer->SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
            mVertexBuffer->SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
            mVertexBuffer->SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);
            mVertexBuffer->SetNormal(offset, 0.0f, 1.0f, 0.0f);
            mVertexBuffer->SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
            mVertexBuffer->SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
            mVertexBuffer->SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);
            if ((z % 2) ^ (x % 2)) {
                mVertexBuffer->SetColor(offset, 0.1f, 0.1f, 0.1f);
                mVertexBuffer->SetColor(offset+1, 0.1f, 0.1f, 0.1f);
                mVertexBuffer->SetColor(offset+2, 0.1f, 0.1f, 0.1f);
                mVertexBuffer->SetColor(offset+3, 0.1f, 0.1f, 0.1f);
            } else {
                mVertexBuffer->SetColor(offset, 0.8f, 0.8f, 0.8f);
                mVertexBuffer->SetColor(offset+1, 0.8f, 0.8f, 0.8f);
                mVertexBuffer->SetColor(offset+2, 0.8f, 0.8f, 0.8f);
                mVertexBuffer->SetColor(offset+3, 0.8f, 0.8f, 0.8f);
            }
        }
    }
    mShader = new Shader;
    mShader->Init("ground.vs", "ground.fs");
    mShader->SetVec4("U_LightPos", 0.0f, 0.0f, 1.0f, 0.0f);//光源位置
    mShader->SetVec4("U_LightAmbient", 1.0f, 1.0f, 1.0f, 1.0f);//环境光
    mShader->SetVec4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);//光源漫反射光的分量
    SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);//材质
    SetDiffuseMaterial(0.6f, 0.6f, 0.6f, 1.0f);//材质对漫反射光的系数
}
void Ground::Draw(glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix) {
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    mShader->Bind(glm::value_ptr(mModelMatrix),glm::value_ptr(viewMatrix),glm::value_ptr(projectionMatrix));
    for (int i = 0; i < 400; i++){
        glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
    }
    mVertexBuffer->Unbind();
}
void Ground::SetAmbientMaterial(float r, float g, float b, float a) {
    mShader->SetVec4("U_AmbientMaterial", r, g, b, a);
}
void Ground::SetDiffuseMaterial(float r, float g, float b, float a) {
    mShader->SetVec4("U_DiffuseMaterial", r, g, b, a);
}
void Ground::SetSpecularMaterial(float r, float g, float b, float a) {
    mShader->SetVec4("U_SpecularMaterial", r, g, b, a);
}
