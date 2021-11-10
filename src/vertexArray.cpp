#include "pch.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
	bind();
}

VertexArray::~VertexArray()
{ glDeleteVertexArrays(1, &ID); }

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl) const
{
	bind();
	vb.bind();

	const auto& elements = vbl.getElements();
	unsigned int offset = 0;
	for(unsigned int i=0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, vbl.getStride(), (const void*)offset);
		offset += element.count*VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{ glBindVertexArray(ID); }

void VertexArray::unbind() const
{ glBindVertexArray(0); }