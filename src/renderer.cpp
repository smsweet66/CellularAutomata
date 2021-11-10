#include "pch.hpp"

namespace Renderer
{
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
	{
		shader.bind();
		va.bind();
		ib.bind();
		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}
}