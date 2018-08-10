//
//  ground.hpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/7/25.
//  Copyright © 2018年 58. All rights reserved.
//

#pragma once
#include "shader.h"
#include "vertexbuffer.hpp"
class Ground {
    VertexBuffer*mVertexBuffer;
    Shader*mShader;
    glm::mat4 mModelMatrix;
public:
    void Init();
    void Draw(glm::mat4 & viewMatrix,glm::mat4 & projectionMatrix);
    void SetAmbientMaterial(float r, float g, float b, float a);
    void SetDiffuseMaterial(float r, float g, float b, float a);
    void SetSpecularMaterial(float r, float g, float b, float a);
};
