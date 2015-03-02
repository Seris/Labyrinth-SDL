labyrinth: *.c headers/*.h
	$(CC) -o $@ *.c -g `sdl2-config --cflags --libs` -lSDL2_image -Iheaders/