#include "pch.hpp"

CellGrid::CellGrid(unsigned int rows, unsigned int cols, float screenWidth, float screenHeight)
: rows(rows), cols(cols), screenWidth(screenWidth), screenHeight(screenHeight), ib(indexes, 6)
{
	positions[0] = 0;		positions[1]  = screenHeight;
	positions[2] = 0;		positions[3]  = screenHeight - 4.0f;
	positions[4] = 4.0f;	positions[5]  = screenHeight;
	positions[6] = 4.0f;	positions[7] = screenHeight - 4.0f;

	vb.addData(positions, sizeof(positions));
	VertexBufferLayout vbl;
	vbl.push<float>(2, GL_FALSE);
	va.addBuffer(vb, vbl);

	living = new bool[rows * cols];
	livingBuffer = new bool[rows * cols];
	std::srand(time(0));
	for(unsigned int i = 0; i < rows * cols; i++)
		living[i] = (std::rand() % 2);
}

CellGrid::~CellGrid()
{
	delete[] living;
	delete[] livingBuffer;
}

void CellGrid::updateGrid()
{
	for(unsigned int i = 0; i < rows; i++) //iteration through each row
	{
		for(unsigned int j = 0; j < cols; j++) //iteration through each column
		{
			int sum = 0;
			for(int r = -1; r <= 1; r++) //iteration through rows of neighbors
			{
				for(int c = -1; c <= 1; c++) //iteration through columns of neighbors
				{
					if(r == 0 && c == 0)
						continue;

					sum += living[((i+r+rows)%rows)*cols + (j+c+cols)%cols];
				}
			}

			if(sum < 2 || sum > 3)
				livingBuffer[i * cols + j] = false;
			else if(sum == 3)
				livingBuffer[i * cols + j] = true;
			else
				livingBuffer[i * cols + j] = living[i * cols + j];
		}
	}

	for(unsigned int i = 0; i < rows * cols; i++)
		living[i] = livingBuffer[i];
}

void CellGrid::drawGrid(const Renderer& renderer, const Shader& shader)
{
	for(unsigned int i = 0; i < rows; i++)
	{
		for(unsigned int j = 0; j < cols; j++)
		{
			if(living[i * cols + j])
			{
				float xPos = j * 5.0f;
				float yPos = -(i * 5.0f);
				glm::mat4 model(1.0f);
				model = glm::translate(model, glm::vec3(xPos, yPos, 0.0f));
				int color = (int)(glfwGetTime() * 16) % 256;
				shader.setUniform4f("u_color", positions[0] + xPos, positions[1] + yPos, -color / 255.0f, 1.0f);
				shader.setUniformMat4("u_model", model);
				renderer.draw(va, ib, shader);
			}
		}
	}
}