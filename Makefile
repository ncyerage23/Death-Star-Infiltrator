# DEATH STAR INFILTRATOR MAKEFILE

BDIR=build
OBJ=build/main.o build/initclose.o build/updatedraw.o

ds: $(OBJ)
	gcc $(OBJ) -lnyfw -o $@

$(BDIR):
	mkdir -p $(BDIR)

$(BDIR)/main.o: src/main.c | $(BDIR)
	gcc -c $< -o $@

$(BDIR)/initclose.o: src/initclose.c | $(BDIR)
	gcc -c $< -o $@

$(BDIR)/updatedraw.o: src/updatedraw.c | $(BDIR)
	gcc -c $< -o $@

clean:
	rm -rf build
	rm -f ds



