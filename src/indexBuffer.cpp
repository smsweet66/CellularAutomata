#include "pch.hpp"

IndexBuffer::IndexBuffer()
:count(0)
{ glGenBuffers(1, &ID); }

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
: count(count)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{ glDeleteBuffers(1, &ID); }

void IndexBuffer::addData(const unsigned int* data, unsigned int count)
{
	this->count = count;
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

void IndexBuffer::unbind() const
{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }