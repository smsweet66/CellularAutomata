#include "pch.hpp"

class Renderer
{
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};