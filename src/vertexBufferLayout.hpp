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

template<typename T>
struct identity { typedef T type; };

class VertexBufferLayout
{
public:
	VertexBufferLayout()
	: stride(0) {}

	template <typename T>
	void push(unsigned int count, GLboolean normalized)
	{ push(count, normalized, identity<T>()); }


	unsigned int getStride() const
	{ return stride; }

	const std::vector<VertexBufferElement>& getElements() const
	{ return elements; }

private:
	unsigned int stride;
	std::vector<VertexBufferElement> elements;

	template <typename T>
	void push(unsigned int count, GLboolean normalized, identity<T>)
	{ std::cout << "Invalid type!" << std::endl; }

	void push(unsigned int count, GLboolean normalized, identity<float>)
	{
		elements.push_back({GL_FLOAT, count, normalized});
		stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	void push(unsigned int count, GLboolean normalized, identity<unsigned int>)
	{
		elements.push_back({GL_UNSIGNED_INT, count, normalized});
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	void push(unsigned int count, GLboolean normalized, identity<unsigned char>)
	{
		elements.push_back({GL_UNSIGNED_BYTE, count, normalized});
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
};