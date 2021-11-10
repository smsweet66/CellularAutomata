#include "pch.hpp"

class Flock
{
public:
	Flock(int size, float screenWidth, float screenHeigt);

	~Flock();

	void update(float hz);

	void drawFlock(const Renderer& renderer, const Shader& shader);

private:
	int size;
	float viewDistance = 200;
	float screenWidth, screenHeight;
	float baseLoc[8] = { -25, 10, 25, 0, 0, 0, -25, -10 };
	float deadZone[3] = { 960, 540, 200 };
	unsigned int indexes[6] = { 0, 1, 2, 1, 2, 3 };
	Boid* flock;
	Boid* flockBuffer;

	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	void separate(int i);

	void align(int i);

	void cohere(int i);
};