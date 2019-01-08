particles = new Particle[N];
for(int i=0; i<N; i++)
	particles[i] = Particle(mass, initial_location_mode);

glUniform3fv(glGetUniformLocation(shader.program, "color"), 1, glm::value_ptr(color));

GLuint vbo, vao;
glGenVertexArrays(1, &vao);
glGenBuffers(1, &vbo);
glBindVertexArray(vao);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
SendParticlesToBuffer(vbo, particles, N);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);