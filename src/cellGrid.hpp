#include "pch.hpp"

class CellGrid
{
private:
	unsigned int rows, cols;
	float screenWidth, screenHeight;

	float positions[8];
	unsigned int indexes[6] = { 0, 1, 2, 1, 2, 3 };

	bool* living;
	bool* livingBuffer;

	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

public:
	CellGrid(unsigned int rows, unsigned int cols, float screenWidth, float screenHeight);

	~CellGrid();

	void updateGrid();

	void drawGrid(const Renderer& renderer, const Shader& shader);
};