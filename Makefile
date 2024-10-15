asteroids: asteroids.c
	#cp asteroids.c /home/jojo/c/Potaje/temp/asteroids/win
	gcc -o asteroids asteroids.c -lSDL2 -lSDL2_gpu -lSDL2_mixer -lSDL2_ttf -lm -O3
debug: asteroids.c
	gcc -o asteroids asteroids.c -lSDL2 -lSDL2_gpu -lSDL2_mixer -lSDL2_ttf -lm -g -O0 -v -da -Q
