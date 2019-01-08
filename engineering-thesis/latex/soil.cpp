int width, height, channels;

unsigned char *ht_map = SOIL_load_image ( "terrain.tga", &width, &height, &channels, SOIL_LOAD_L );
int save_result = SOIL_save_image ( "new_terrain.dds", SOIL_SAVE_TYPE_DDS, width, height, channels, ht_map );

SOIL_free_image_data(ht_map);