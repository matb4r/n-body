#pragma once
#include "GLM/glm.hpp"
#include "GLM/gtc/random.hpp"

struct Particle
{
	float mass;
	glm::vec3 location;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 force;

	Particle() {}

	Particle(float mass, int initial_location)
	{
		this->mass = mass;

		switch(initial_location)
		{
			case 0:
				// sphere
				location = glm::vec3(glm::sphericalRand(1.5f)); break;
			case 1:
				// gauss
				location = glm::vec3(glm::gaussRand(glm::vec3(0), glm::vec3(1))); break;
			case 2:
				// cube
				location = glm::vec3(sin(rand()), sin(rand()), sin(rand())); break;
		}
	}

};

