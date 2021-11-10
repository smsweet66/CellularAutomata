#pragma once

class Boid
{
public:
	Boid()
	: location{0}, velocity{0}, acceleration{0} {}

	Boid(const Boid& other)
	{
		location[0] = other.location[0];			location[1] = other.location[1];
		velocity[0] = other.velocity[0];			velocity[1] = other.velocity[1];
		acceleration[0] = other.acceleration[0];	acceleration[1] = other.acceleration[1];
	}

	void init(float x, float y, float vx, float vy)
	{
		location[0] = x;	location[1] = y;
		velocity[0] = vx;	velocity[1] = vy;
	}

	static float distance(const Boid& b1, const Boid& b2)
	{
		float xSquared = (b1.location[0] - b2.location[0]) * (b1.location[0] - b2.location[0]);
		float ySquared = (b1.location[1] - b2.location[1]) * (b1.location[1] - b2.location[1]);
		return sqrt(xSquared + ySquared);
	}

	void setSpeed(float speed)
	{
		float currSpeed = sqrt(velocity[0] * velocity[0] + velocity[1] * velocity[1]);
		velocity[0] = speed * velocity[0] / currSpeed;
		velocity[1] = speed * velocity[1] / currSpeed;
	}

	float getX()
	{ return location[0]; }

	float getY()
	{ return location[1]; }

	void setLocation(float x, float y)
	{
		location[0] = x; location[1] = y;
	}

	float getVx()
	{ return velocity[0]; }

	float getVy()
	{ return velocity[1]; }

	void setVelocity(float vx, float vy)
	{
		velocity[0] = vx; velocity[1] = vy;
	}

	float getAx()
	{ return acceleration[0]; }

	float getAy()
	{ return acceleration[1]; }

	void setAcceleration(float ax, float ay)
	{
		acceleration[0] = ax; acceleration[1] = ay;
	}

	float getAngle()
	{
		float angle = atan(velocity[1]/velocity[0]);
		if(velocity[0] >= 0 && velocity[1] >= 0) //first quadrant
			return angle;
		if(velocity[0] >= 0 && velocity[1] < 0) //fourth quadrant
			return 2 * 3.14159265f + angle;
		
		return 3.14159265f + angle;
	}

private:
	float location[2];		//location of the center of the boid
	float velocity[2];		//velocity of the boid
	float acceleration[2];	//acceleration of the boid
};