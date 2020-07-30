#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct shaderProgramSourse
{
	std::string vertexSource;
	std::string fragmentSource;
};

class shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	shader(const std::string& filepath);
	~shader();

	void bind() const;
	void unbind() const;

	// set uniforms
	void setUniform1i(const std::string& name, int value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	shaderProgramSourse parseShader(const std::string& filePath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int getUniformlocation(const std::string& name);
};
