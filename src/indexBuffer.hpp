#include "pch.hpp"

class IndexBuffer
{
public:
	IndexBuffer();

	IndexBuffer(const unsigned int* data, unsigned int count);

	~IndexBuffer();

	void addData(const unsigned int* data, unsigned int count);

	void bind() const;

	void unbind() const;

	unsigned int getCount() const
	{ return count; }

private:
	unsigned int ID;
	unsigned int count;
};