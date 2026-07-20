# DEATH STAR INFILTRATOR MAKEFILE

LDFLAGS=-pg
CFLAGS=-Wall -Wextra -g -pg
BDIR=build
OBJ=build/main.o build/initclose.o build/updatedraw.o build/player.o build/collision.o

ds: $(OBJ)
	gcc $(LDFLAGS) $(OBJ) -lnyfw -o $@

$(BDIR):
	mkdir -p $(BDIR)

$(BDIR)/main.o: src/main.c | $(BDIR)
	gcc $(CFLAGS) -c $< -o $@

$(BDIR)/initclose.o: src/initclose.c | $(BDIR)
	gcc $(CFLAGS) -c $< -o $@

$(BDIR)/updatedraw.o: src/updatedraw.c | $(BDIR)
	gcc $(CFLAGS) -c $< -o $@

$(BDIR)/player.o: src/player.c | $(BDIR)
	gcc $(CFLAGS) -c $< -o $@

$(BDIR)/collision.o: src/collision.c | $(BDIR)
	gcc $(CFLAGS) -c $< -o $@


clean:
	rm -rf build
	rm -f ds gmon.out prof.txt 

full:
	make clean
	make

