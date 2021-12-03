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
//#include "tests/TestClearColor.h"




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
        float positions[] = {
            //POSITION                        COLOR
            -0.5f, -0.5f, -0.5f, 1.0f,      0.9f, 0.1f, 0.1f, 1.0f,  //BLB (0)
             0.5f, -0.5f, -0.5f, 1.0f,      0.9f, 0.2f, 0.1f, 1.0f,  //BRB (1)
             0.5f,  0.5f, -0.5f, 1.0f,      0.7f, 0.3f, 0.1f, 1.0f,  // BRT(2)
            -0.5f,  0.5f, -0.5f, 1.0f,      0.6f, 0.4f, 0.1f, 1.0f,  //BLT (3)
                                                      
            -0.5f,  0.5f,  0.5f, 1.0f,      0.4f, 0.1f, 0.6f, 1.0f,  //FLT (4)
            -0.5f, -0.5f,  0.5f, 1.0f,      0.3f, 0.1f, 0.7f, 1.0f,  //FLB (5)
             0.5f, -0.5f,  0.5f, 1.0f,      0.2f, 0.1f, 0.8f, 1.0f,  //FRB (6)
             0.5f,  0.5f,  0.5f, 1.0f,      0.1f, 0.1f, 0.9f, 1.0f   //FRT (7)
        };


        uint32_t indicies[] = {
            
            0, 1,
            1, 2,
            2, 3,
            3, 0,

            0, 5,
            5, 4,
            4, 3,

            1, 6,
            6, 7,
            7, 2,

            4, 5,
            5, 6,
            6, 7,
            7, 4
        };

        std::cout << glGetString(GL_VERSION);
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        uint32_t buffer;
        VertexArray va;
        VertexBuffer vb(positions, 8 * 8 * sizeof(float));


        VertexBufferLayout layout;
        layout.Push<float>(4);
        layout.Push<float>(4);
        va.AddBuffer(vb, layout);

     
        IndexBuffer ib(indicies, 28);
        
        glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        

        Shader shader("res/Basic.shader");
        shader.Bind();

        
        //Texture texture("res/motor.png");
        //texture.Bind();
        //shader.SetUniform1i("u_Texture", 0);


        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();



        Renderer renderer;
        
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        ImGui::StyleColorsDark();

        
        glm::vec3 translation(0, 0, 0);
        glm::vec3 axisY(0.0f, 1.0f, 0.0f);
        glm::vec3 axisX(1.0f, 0.0f, 0.0f);
        glm::vec3 axisZ(0.0f, 0.0f, 1.0f);

        float angleY = 0.0f;
        float angleX = 0.0f;
        float angleZ = 0.0f;
        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            model = model * glm::rotate(model, glm::radians(angleY),axisY);
            model = model * glm::rotate(model, glm::radians(angleX),axisX);
            model = model * glm::rotate(model, glm::radians(angleZ),axisZ);
            glm::mat4 mvp = proj * view * model;
            
            shader.Bind();
            shader.SetUniform4Matf("u_MVP", mvp);
            shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

            va.Bind();
            ib.Bind();

            renderer.DrawLines(va, ib, shader);
           

            
            {
                ImGui::SliderFloat3("Translation", &translation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat("Rotation Y", &angleY, -90.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat("Rotation X", &angleX, -90.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat("Rotation Z", &angleZ, -90.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            }


            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            //glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    

    glfwTerminate();
    return 0;
}