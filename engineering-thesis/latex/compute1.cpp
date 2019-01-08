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