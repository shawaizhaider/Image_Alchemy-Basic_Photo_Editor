all:
	gcc -I src/include -L src/lib -o sdltest.exe sdltest.c -lmingw32 -lSDL2main -lSDL2