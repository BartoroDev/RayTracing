#pragma once

#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace test {

	class TestCubeSkeleton : public Test
	{
	public:
		TestCubeSkeleton();
		~TestCubeSkeleton();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_CubeScale, m_AngleAxisX, m_AngleAxisY, m_AngleAxisZ;
		Shader m_Shader;
		glm::vec3 m_Translation;
		Renderer m_Renderer;
		VertexArray m_va;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
		glm::vec3 m_axisY;
		glm::vec3 m_axisZ;
		glm::vec3 m_axisX;
		glm::mat4 m_MVP;
	};
}
