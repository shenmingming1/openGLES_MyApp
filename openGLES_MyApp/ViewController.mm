//
//  ViewController.m
//  openGLES_MyApp
//
//  Created by 58 on 2018/7/25.
//  Copyright © 2018年 58. All rights reserved.
//

#import "ViewController.h"
#include "utils.h"
#include "scene.h"
#include "shaderScene.hpp"
unsigned char * LoadFileContent(const char*path,int&filesize){
    unsigned char*fileContent=nullptr;
    filesize=0;
    NSString *nsPath=[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:path] ofType:nil];
    NSData*data=[NSData dataWithContentsOfFile:nsPath];
    if([data length]>0){
        filesize=[data length];
        fileContent=new unsigned char[filesize+1];
        memcpy(fileContent, [data bytes], filesize);
        fileContent[filesize]='\0';
    }
    return fileContent;
}
float GetFrameTime(){
    return 0.033f;
}
@interface ViewController ()
@property (strong, nonatomic) EAGLContext *context;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];//3.0
    if(!self.context)
    {
        self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];//2.0
    }
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    //
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:self.context];
    [self initScene];

}
-(void)initScene
{
//    Init();
    CGRect rect=[[UIScreen mainScreen] bounds];
//    SetViewPortSize(rect.size.width,rect.size.height);
    InitShaderScene();
    SetViewPortSizeShaderScene(rect.size.width,rect.size.height);
}
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
//    Draw();
    DrawShaderScene();
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
