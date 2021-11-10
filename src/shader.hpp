#include "pch.hpp"

struct ShaderSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
public:
	Shader(const std::string& filePath);

	~Shader();

	void bind() const;

	void unbind() const;

	void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const;

	void setUniformMat4(const std::string& name, const glm::mat4& matrix) const;

private:
	unsigned int compileShader(unsigned int type, const std::string& source);

	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

	ShaderSource parseShader();

	unsigned int getUniformLocation(const std::string& name) const;

	mutable std::unordered_map<std::string, int> uniformLocationCache;
	std::string filePath;
	unsigned int ID;
};