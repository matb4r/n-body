int width, height;
unsigned char* image = SOIL_load_image("Data/particle.png", &width, &height, 0, SOIL_LOAD_AUTO);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
glGenerateMipmap(GL_TEXTURE_2D);
SOIL_free_image_data(image);