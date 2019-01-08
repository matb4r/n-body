for (int i = 1; i < argc; i++)
{
	if (strcmp(argv[i], "-n") == 0)
		N = atoi(argv[++i]);
	else if (strcmp(argv[i], "-m") == 0)
		mass = atof(argv[++i]);
	else if (strcmp(argv[i], "-r") == 0)
	{
		color.r = atof(argv[++i]);
		color.g = atof(argv[++i]);
		color.b = atof(argv[++i]);
	}
	else if (strcmp(argv[i], "-l") == 0)
		initial_location_mode = atoi(argv[++i]);
	else if (strcmp(argv[i], "-c") == 0)
		compute_mode = atoi(argv[++i]);
	else if (strcmp(argv[i], "-d") == 0)
	{
		win_width = atoi(argv[++i]);
		win_height = atoi(argv[++i]);
	}
	else if (strcmp(argv[i], "-f") == 0)
		fullscreen = true;
	else if (strcmp(argv[i], "-h") == 0)
	{
		std::cout << "\t-n [count] : number of particles; default = 600"
				"\n\t-m [mass] : mass of each particle; default = 0.001"
				"\n\t-r [r] [g] [b] : color of each particle; default = 1.0 0.3 0.1"
				"\n\t-l [initial location mode] : initial location mode (0-2); default = 0"
				"\n\t-c [compute mode] : compute mode (0-1); default = 1"
				"\n\t-d [width] [height] : window width and height; default = 800 600"
				"\n\t-f : fullscreen mode"
				"\n\t-h : show this help";
		return 0;
	}

}