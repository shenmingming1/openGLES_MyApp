//
//  FrameBufferObject.hpp
//  openGLES_MyApp
//
//  Created by 58 on 2018/8/8.
//  Copyright © 2018年 58. All rights reserved.
//
#pragma once
#include "ggl.h"
class FrameBufferObject{
public:
    GLuint mFrameBufferObject;
    GLint mPrevFrameBuffer;
    std::map<std::string,GLuint> mBuffers;
    std::vector<GLenum> mDrawBuffers;
public:
    FrameBufferObject();
    void AttachColorBuffer(const char*bufferName,GLenum attachment,int width,int height);
    void AttachDepthBuffer(const char*bufferName,int width,int height);
    void Finish();
    void Bind();
    void UnBind();
    GLuint GetBuffer(const char*bufferName);
};
