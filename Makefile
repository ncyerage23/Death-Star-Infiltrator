# makefile thing (add more explanation later)



CFLAGS 	:= -Iengine -MMD -MP
# -Wall and -Wextra were pissing me off
# probably for a reason tho


# object dirs
objs = $(patsubst %.c,build/%.o,$(wildcard $(1)/*.c))


# modules
CORE		:= $(call objs,engine/core)
CANVAS		:= $(call objs,engine/canvas)
MOUSE		:= $(call objs,engine/mouse)
FILES		:= $(call objs,engine/files)
DATA		:= $(call objs,engine/data)


# apps
bin/screentest: $(call objs,apps/screentest) $(CORE) $(CANVAS)
	@mkdir -p $(@D)
	gcc $^ -o $@

bin/mapmaker: $(call objs,apps/mapmaker) $(CORE) $(CANVAS) $(MOUSE)
	@mkdir -p $(@D)
	gcc $^ -o $@

bin/tilepainter: $(call objs,apps/tilepainter) $(CORE) $(CANVAS) $(MOUSE)
	@mkdir -p $(@D)
	gcc $^ -o $@

# tests
bin/tile_file_test: $(call objs,tests/tile_file_test) $(CORE) $(CANVAS) $(DATA) $(FILES)
	@mkdir -p $(@D)
	gcc $^ -o $@


# binary name shorthand
tile_file_test: bin/tile_file_test
screentest:	bin/screentest
mapmaker:	bin/mapmaker
tilepainter:	bin/tilepainter
all: 		screentest mapmaker tilepainter


# compiling all the .c files
build/%.o: %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@


clean:
	rm -rf build bin


.PHONY: all clean screentest mapmaker tilepainter tile_file_test

-include $(shell find build-name '*.d' 2>/dev/null)


