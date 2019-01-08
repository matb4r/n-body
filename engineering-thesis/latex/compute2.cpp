for (int i = 0; i < N; i++)
{
	p[i].acceleration = p[i].force / p[i].mass;
	p[i].velocity += p[i].acceleration * delta_time;
	p[i].location += p[i].velocity * delta_time;

	p[i].force = glm::vec3(0, 0, 0);
}