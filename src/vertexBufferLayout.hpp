#include "pch.hpp"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	GLboolean normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch(type)
		{
		case GL_FLOAT :
			return 4;

		case GL_UNSIGNED_INT :
			return 4;

		case GL_UNSIGNED_BYTE :
			return 1;

		default:
			return 0;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
	: stride(0) {}

	template <typename T>
	void push(unsigned int count, GLboolean normalized)
	{ static_assert(false); }

	template <>
	void push<float>(unsigned int count, GLboolean normalized)
	{ 
		elements.push_back({GL_FLOAT, count, normalized});
		stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template <>
	void push<unsigned int>(unsigned int count, GLboolean normalized)
	{ 
		elements.push_back({GL_UNSIGNED_INT, count, normalized});
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template <>
	void push<unsigned char>(unsigned int count, GLboolean normalized)
	{
		elements.push_back({GL_UNSIGNED_BYTE, count, normalized});
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	unsigned int getStride() const
	{ return stride; }

	const std::vector<VertexBufferElement>& getElements() const
	{ return elements; }

private:
	unsigned int stride;
	std::vector<VertexBufferElement> elements;
};