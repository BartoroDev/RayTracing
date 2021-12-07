#include "TestCubeSkeleton.h"

#include "imgui/imgui.h"

namespace test {

    TestCubeSkeleton::TestCubeSkeleton()
        :m_CubeScale(1.0f), m_AngleAxisX(0.0f), m_AngleAxisY(0.0f), m_AngleAxisZ(0.0f), m_Shader("res/Basic.shader"), m_Translation(0.0, 0.0, 0.0),
        m_axisY(0.0f, 1.0f, 0.0f), m_axisZ(0.0f, 0.0f, 1.0f), m_axisX(1.0f, 0.0f, 0.0f)
    {


        float Verticies[]{
        -0.5f, -0.5f, -0.5f, 1.0f,   0.9f, 0.1f, 0.1f, 1.0f,  //BLB (0)
         0.5f, -0.5f, -0.5f, 1.0f,   0.9f, 0.2f, 0.1f, 1.0f,  //BRB (1)
         0.5f,  0.5f, -0.5f, 1.0f,   0.7f, 0.3f, 0.1f, 1.0f,  // BRT(2)
        -0.5f,  0.5f, -0.5f, 1.0f,   0.6f, 0.4f, 0.1f, 1.0f,  //BLT (3)

        -0.5f,  0.5f,  0.5f, 1.0f,   0.4f, 0.1f, 0.6f, 1.0f,  //FLT (4)
        -0.5f, -0.5f,  0.5f, 1.0f,   0.3f, 0.1f, 0.7f, 1.0f,  //FLB (5)
         0.5f, -0.5f,  0.5f, 1.0f,   0.2f, 0.1f, 0.8f, 1.0f,  //FRB (6)
         0.5f,  0.5f,  0.5f, 1.0f,   0.1f, 0.1f, 0.9f, 1.0f   //FRT (7)
        };


        uint32_t Indicies[]{
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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_vb.AddData(Verticies, 8 * 8 * sizeof(float));


        VertexBufferLayout layout;
        layout.Push<float>(4);
        layout.Push<float>(4);


        m_va.AddBuffer(m_vb, layout);
        m_ib.BindData(Indicies, 28);

    }

    TestCubeSkeleton::~TestCubeSkeleton()
    {
    }

    void TestCubeSkeleton::OnUpdate(float deltaTime)
    {
    }

    void TestCubeSkeleton::OnRender()
    {
        glm::vec3 scale = glm::vec3(m_CubeScale);
        glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        glm::mat4 model = glm::scale(glm::mat4(1.0f),scale);
        model = glm::translate(model, m_Translation);
        model = model * glm::rotate(model, glm::radians(m_AngleAxisX), m_axisX);
        model = model * glm::rotate(model, glm::radians(m_AngleAxisY), m_axisY);
        model = model * glm::rotate(model, glm::radians(m_AngleAxisZ), m_axisZ);
        glm::mat4 mvp = proj * view * model;

        m_Shader.Bind();
        m_Shader.SetUniform4Matf("u_MVP", mvp);


        m_Renderer.DrawLines(m_va, m_ib, m_Shader);
    }

    void TestCubeSkeleton::OnImGuiRender()
    {

        ImGui::SliderFloat3("Translation", &m_Translation[0], -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("Rotation X", &m_AngleAxisX, -90.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("Rotation Y", &m_AngleAxisY, -90.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("Rotation Z", &m_AngleAxisZ, -90.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("Scale ", &m_CubeScale, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    }

}