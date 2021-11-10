#include "pch.hpp"

VertexBuffer::VertexBuffer()
{ glGenBuffers(1, &ID); }

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{ glDeleteBuffers(1, &ID); }

void VertexBuffer::addData(const void* data, unsigned int size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{ glBindBuffer(GL_ARRAY_BUFFER, ID); }

void VertexBuffer::unbind() const
{ glBindBuffer(GL_ARRAY_BUFFER, 0); }