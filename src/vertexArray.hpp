#include "pch.hpp"

class VertexArray
{
public:
	VertexArray();

	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl) const;

	void bind() const;

	void unbind() const;

private:
	unsigned int ID;
};