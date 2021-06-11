//
//  main.cpp
//  OpenGL
//
//  Created by x on 2021/4/22.
//

#include <stdio.h>

//#include "glad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
//using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLFWwindow *window;

// 窗口尺寸变化的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 检查窗口的输入是否是esc
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        // 标记窗口需要关闭
        glfwSetWindowShouldClose(window, true);
    }
}

void initGLFW() {
    // 初始化GLFW
    glfwInit();
    // 设置大版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // 设置小版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 设置核心模式,意味着不向后兼容
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    // Mac电脑上需要加上,确保上面的内容生效.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void createWindow() {
    // 创建窗口,并设置参数
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    // 通知GLFW,将窗口的上下文为当前线程的主上下文.
    glfwMakeContextCurrent(window);
}

void initGLAD() {
    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    // 告诉OpenGL渲染窗口的尺寸大小,这样OpenGL才能知道怎样根据窗口大小显示数据和坐标。我们可以通过调用glViewport函数来设置窗口的维度(Dimension)：
    // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素)
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    
    // 设置window大小变化时的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void renderLoop() {
    // 检查glfw是否被标记退出,非0就是要求退出
    while (glfwWindowShouldClose(window) == 0) {
        
        // 输入检测,esc是否被按下,按下就退出
        processInput(window);
        
        // 指定颜色填充window
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 交换颜色缓冲,将会作为输出显示在屏幕上,
        glfwSwapBuffers(window);
        // 检查有没有触发什么事件(键盘移动,鼠标点击),更新窗口状态,并调用对应的回调
        glfwPollEvents();
    }
    // 释放/删除之前分配的所有资源
    glfwTerminate();
}

int main(int argc, char *argv[]) {
    initGLFW();
    createWindow();
    initGLAD();
    renderLoop();
    return 0;
}
