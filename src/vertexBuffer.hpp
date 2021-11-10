#include "pch.hpp"

class VertexBuffer
{
public:
	VertexBuffer();

	VertexBuffer(const void* data, unsigned int size);

	~VertexBuffer();

	/*
	adds data to the vertex buffer
	DATA SHOULD ONLY BE ADDED ONCE
	*/
	void addData(const void* data, unsigned int size);

	/*
	binds the vertex buffer
	*/
	void bind() const;

	/*
	unbinds the vertex buffer
	*/
	void unbind() const;

private:
	unsigned int ID;
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;
};