void SendParticlesToBuffer(GLuint vbo, Particle* p, int N)
{
	GLfloat* all_floats = new GLfloat[N * 3];

	for (int i = 0, j = 0; i < N; i++)
	{
		all_floats[j] = p[i].location.x; j++;
		all_floats[j] = p[i].location.y; j++;
		all_floats[j] = p[i].location.z; j++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * N * sizeof(GLfloat), all_floats, GL_STATIC_DRAW);
}