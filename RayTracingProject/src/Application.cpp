#include "imgui/imgui_impl_glfw.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/TestClearColor.h"
#include "tests/TestCubeSkeleton.h"


int main(void)
{
    const char* glsl_version = "#version 130";
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */

    window = glfwCreateWindow(960, 720, "Application", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK)
        std::cout << "Memy b³¹d!" << std::endl;
    {
        
        std::cout << glGetString(GL_VERSION);
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        ImGui::StyleColorsDark();

      
        test::TestCubeSkeleton test;
        
       

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            test.OnUpdate(0.0f);
            test.OnRender();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
           
            test.OnImGuiRender();
            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            

            glfwSwapBuffers(window);


            glfwPollEvents();
        }

    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    

    glfwTerminate();
    return 0;
}