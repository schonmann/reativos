run: game cleanup
	./game
cleanup: game
	rm *.o
game: all.o
	gcc -o game *.o  -lSDL2 -lSDL2_image -lm
debug: all.o
	gcc -o game *.o  -DDEBUG -lSDL2 -lSDL2_image -lm

# Compile all .cpp object files for future linking.

all.o:
	find . -type f -name '*.c' -exec sh -c 'gcc {} -Iinclude -c $(basename {} .c)' \;

