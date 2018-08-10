//
//  fullscreenquad.hpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/8/8.
//  Copyright © 2018年 58. All rights reserved.
//

#pragma once
#include "ggl.h"
#include "vertexbuffer.hpp"
#include "shader.h"
class FullScreenQuad{
public:
    VertexBuffer *mVertexBuffer;
    Shader* mShader;
    void Init();
    void Draw();
    void DrawToLeftTop();
    void DrawToRightTop();
    void DrawToLeftBottom();
    void DrawToRightBottom();
};
