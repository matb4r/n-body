void PrintInfo()
{
	printf("Simulation info:\n");
	printf("\tTime: %0.2fs\n", glfwGetTime());
	printf("\tAverage FPS: %0.2f\n", average_fps_sum/average_fps_count);
	printf("\tCamera position: [%.2f, %.2f, %.2f]\n", camera.position.x, camera.position.y, camera.position.z);
	printf("\tField of view: %f\n", camera.fov);
	printf("\tNumber of particles %d\n", N);
	printf("\tMass of each particle: %f\n", mass);
	printf("\tColor: [%.2f, %.2f, %.2f]\n", color.r, color.g, color.b);
	printf("\tInitial location: %d\n", initial_location_mode);
	printf("\tCompute mode: %d\n", compute_mode);
}