#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

// mode 0
void ComputeNextPositions(GLuint vbo, Particle* p, int N, GLfloat delta_time, float G = 1.0f)
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			glm::vec3 location_difference = p[j].location - p[i].location;
			float distance = glm::length(location_difference) + 0.1f;
			glm::vec3 force = (G * p[i].mass * p[j].mass) / (distance * distance) * glm::normalize(location_difference);

			p[i].force += force;
			p[j].force -= force;
		}
	}

	for (int i = 0; i < N; i++)
	{
		p[i].acceleration = p[i].force / p[i].mass;
		p[i].velocity += p[i].acceleration * delta_time;
		p[i].location += p[i].velocity * delta_time;

		p[i].force = glm::vec3(0, 0, 0);
	}
}

// mode 1
void ComputeNextPositions_TBB_Outer(GLuint vbo, Particle* p, int N, GLfloat delta_time, float G = 1.0f)
{
	tbb::parallel_for(0, N-1, [&](int i) {
		for (int j = i+1; j < N; j++)
		{
			glm::vec3 location_difference = p[j].location - p[i].location;
			float distance = glm::length(location_difference) + 0.1f;
			glm::vec3 force = (G * p[i].mass * p[j].mass) / (distance * distance) * glm::normalize(location_difference);

			p[i].force += force;
			p[j].force -= force;
		}
	});

	tbb::parallel_for(0, N, [&](int i)
	{
		p[i].acceleration = p[i].force / p[i].mass;
		p[i].velocity += p[i].acceleration * delta_time;
		p[i].location += p[i].velocity * delta_time;

		p[i].force = glm::vec3(0, 0, 0);
	});
}

// mode 2
void ComputeNextPositions_TBB_Both(GLuint vbo, Particle* p, int N, GLfloat delta_time, float G = 1.0f)
{
	tbb::parallel_for(0, N-1, [&](int i)
	{
		tbb::parallel_for(i+1, N, [&](int j)
		{
			glm::vec3 location_difference = p[j].location - p[i].location;
			float distance = glm::length(location_difference) + 0.1f;
			glm::vec3 force = (G * p[i].mass * p[j].mass) / (distance * distance) * glm::normalize(location_difference);

			p[i].force += force;
			p[j].force -= force;

		});
	});

	tbb::parallel_for(0, N, [&](int i)
	{
		p[i].acceleration = p[i].force / p[i].mass;
		p[i].velocity += p[i].acceleration * delta_time;
		p[i].location += p[i].velocity * delta_time;

		p[i].force = glm::vec3(0, 0, 0);
	});
}

// mode 3
void ComputeNextPositions_TBB_BlockedRange(GLuint vbo, Particle* p, int N, GLfloat delta_time, float G = 1.0f)
{
	tbb::parallel_for(tbb::blocked_range2d<int>(0, N, 0, N),
		[=](const tbb::blocked_range2d<int> &r) {
		for (int i = r.cols().begin(); i != r.cols().end(); ++i)
		{
			for (int j = r.rows().begin(); j != r.rows().end(); ++j)
			{
				if (i != j)
				{
					glm::vec3 location_difference = p[j].location - p[i].location;
					float distance = glm::length(location_difference) + 0.1f;
					glm::vec3 force = (G * p[i].mass * p[j].mass) / (distance * distance) * glm::normalize(location_difference);

					p[i].force += force;
				}
			}
		}
	});

	tbb::parallel_for(0, N, [&](int i)
	{
		p[i].acceleration = p[i].force / p[i].mass;
		p[i].velocity += p[i].acceleration * delta_time;
		p[i].location += p[i].velocity * delta_time;

		p[i].force = glm::vec3(0, 0, 0);
	});
}
