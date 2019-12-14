build:
	g++ -w -std=c++14 -Wfatal-errors \
	./*.cpp \
	-o tetris \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./tetris;

run:
	./tetris;