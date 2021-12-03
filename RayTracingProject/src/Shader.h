#pragma once
#include <String>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};


class Shader
{
private:
	std::string m_FilePath;
	uint32_t m_RendererID;
	std::unordered_map<std::string, int32_t> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind();

	//Set Uniforms
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform4Matf(const std::string& name, const glm::mat4& matrix);
	void SetUniform1i(const std::string& name, int32_t v0);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	uint32_t CompileShader(const std::string& source, uint32_t type);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
;	uint32_t GetUniformLocation(const std::string& name);
};
