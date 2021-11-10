#include "pch.hpp"

Flock::Flock(int size, float screenWidth, float screenHeight)
: size(size), screenWidth(screenWidth), screenHeight(screenHeight), vb(baseLoc, sizeof(baseLoc)), ib(indexes, 6)
{
	std::srand(time(0));
	flock = new Boid[size];
	flockBuffer = new Boid[size];
	for(int i=0; i<size; i++)
		flock[i].init(rand()%(int)screenWidth, rand()%(int)screenHeight, rand()%51 - 25, rand()%51 - 25);

	VertexBufferLayout vbl;
	vbl.push<float>(2, GL_FALSE);
	va.addBuffer(vb, vbl);
}

Flock::~Flock()
{
	delete[] flock;
	delete[] flockBuffer;
}

/*
updates the boid based on the surrounding boids
*/
void Flock::update(float hz)
{
	for(int i=0; i<size; i++)
	{
		flock[i].setAcceleration(0.0f, 0.0f);
		flockBuffer[i] = flock[i];
		float x = flockBuffer[i].getX() + flockBuffer[i].getVx()/hz;
		if(x < 0)
			x = screenWidth - x;
		else if(x > screenWidth)
			x -= screenWidth;

		float y = flockBuffer[i].getY() + flockBuffer[i].getVy()/hz;
		if(y < 0)
			y = screenHeight - y;
		else if(y > screenHeight)
			y -= screenHeight;

		flockBuffer[i].setLocation(x, y);

		separate(i);
		align(i);
		cohere(i);
		flockBuffer[i].setVelocity(flockBuffer[i].getVx() + flockBuffer[i].getAx()/hz, flockBuffer[i].getVy() + flockBuffer[i].getAy()/hz);
		flockBuffer[i].setSpeed(400.0f);
	}

	for(int i=0; i<size; i++)
		flock[i] = flockBuffer[i];
}

/*
forces the boid away from the others if they are too close
also steers boids away from dead zones;
*/
void Flock::separate(int i)
{
	int nearCount = 0;
	for (int j = 0; j < size; j++)
	{
		if (i == j)
			continue;

		float dist = Boid::distance(flock[i], flock[j]);
		if (dist < 0.000001)
			continue;
		else if(dist < viewDistance)
		{
			nearCount++;
			float xAccel = 1450.0f*(flock[i].getX() - flock[j].getX()) / dist;
			float yAccel = 1450.0f*(flock[i].getY() - flock[j].getY()) / dist;
			flockBuffer[i].setAcceleration(flockBuffer[i].getAx() + xAccel, flockBuffer[i].getAy() + yAccel);
		}
	}

	float dist = sqrt(std::pow(flock[i].getX()-deadZone[0], 2) + std::pow(flock[i].getY() - deadZone[1], 2)) - deadZone[2];
	if(dist < viewDistance)
	{
		nearCount++;
		float xAccel = 20000.0f * (flock[i].getX() - deadZone[0]) / (dist*dist);
		float yAccel = 20000.0f * (flock[i].getY() - deadZone[1]) / (dist*dist);
		flockBuffer[i].setAcceleration(flockBuffer[i].getAx() + xAccel, flockBuffer[i].getAy() + yAccel);
	}

	if(nearCount != 0)
		flockBuffer[i].setAcceleration(flockBuffer[i].getAx()/nearCount, flockBuffer[i].getAy()/nearCount);
}

/*
Alligns the velocity to the average of the nearby boids
*/
void Flock::align(int i)
{
	int nearCount = 0;
	float avgVel[2] = {0};
	for(int j=0; j<size; j++)
	{
		if(i == j)
			continue;

		float dist = Boid::distance(flock[i], flock[j]);
		if(dist < viewDistance)
		{
			nearCount++;
			avgVel[0] += flock[j].getVx();
			avgVel[1] += flock[j].getVy();
		}
	}

	if(nearCount != 0)
	{
		avgVel[0] /= nearCount; avgVel[1] /= nearCount;
		flockBuffer[i].setAcceleration(flockBuffer[i].getAx() + 10.0f*(avgVel[0]-flockBuffer[i].getVx()),
									   flockBuffer[i].getAy() + 10.0f*(avgVel[1]-flockBuffer[i].getVy()));
	}
}

/*
Moves the boid to the average location of the boids around it
*/
void Flock::cohere(int i)
{
	int nearCount = 0;
	float avgLoc[2] = {0};
	for(int j=0; j<size; j++)
	{
		if(i == j)
			continue;

		float dist = Boid::distance(flock[i], flock[j]);
		if(dist < viewDistance)
		{
			nearCount++;
			avgLoc[0] += flock[j].getX();
			avgLoc[1] += flock[j].getY();
		}
	}

	if (nearCount != 0)
	{
		avgLoc[0] /= nearCount; avgLoc[1] /= nearCount;
		flockBuffer[i].setAcceleration(flockBuffer[i].getAx() + 10.5f*(avgLoc[0] - flockBuffer[i].getX()),
									   flockBuffer[i].getAy() + 10.5f*(avgLoc[1] - flockBuffer[i].getY()));
	}
}

/*
Draws the flock of boids to the screen
*/
void Flock::drawFlock(const Shader& shader)
{
	for(int i=0; i<size; i++)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(flock[i].getX(), flock[i].getY(), 0.0f));
		model = glm::rotate(model, flock[i].getAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setUniformMat4("u_model", model);
		shader.setUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
		Renderer::draw(va, ib, shader);
	}
}