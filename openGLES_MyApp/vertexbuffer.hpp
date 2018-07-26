//
//  vertexbuffer.hpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/7/25.
//  Copyright © 2018年 58. All rights reserved.
#pragma once
#include "ggl.h"
struct Vertex{
    float Position[4];
    float Color[4];
    float Texcoord[4];
    float Normal[4];
};
class VertexBuffer {
public:
    GLuint mVBO;
    Vertex *mVertexes;
    int mVertexCount;
    void SetSize(int vertexCount);
    void SetPosition(int index, float x, float y, float z, float w = 1.0f);
    void Bind();
    void Unbind();
    void SetColor(int index, float r, float g, float b, float a=1.0);
    void SetTexcoord(int index, float x, float y);
    void SetNormal(int index, float x, float y, float z);
    Vertex&Get(int index);
};
