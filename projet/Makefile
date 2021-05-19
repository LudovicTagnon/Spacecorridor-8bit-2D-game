CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h sdl2-ttf-light.h sdl2data.h graphics.h constantes.h 

SRC = main.c sdl2-light.c sdl2-ttf-light.c data.c graphics.c
OBJ = $(SRC:%.c=%.o)

TST = tests.c data.c 

PROG = spacecorridor

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacecorridor: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	
tests: $(TST)
	gcc $(CFLAGS) $(TST) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html

