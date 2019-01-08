while (!glfwWindowShouldClose(window))
{
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	UpdateDelta();
	ShowFPS(window);
	MoveCamera();

	switch(compute_mode)
	{
		case 0:
			ComputeNextPositions(vbo, particles, N, delta_time); break;
		case 1:
			ComputeNextPositions_TBB_Outer(vbo, particles, N, delta_time); break;
	}

	SendParticlesToBuffer(vbo, particles, N);

	glm::mat4 model;
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.fov) , (float)win_width / (float)win_height, 0.01f, 1000.f);

	glm::mat4 mvp = projection * view * model;
	glUniformMatrix4fv(glGetUniformLocation(shader.program, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	glDrawArrays(GL_POINTS, 0, N);
	glfwSwapBuffers(window);
}