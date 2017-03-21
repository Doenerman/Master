BIN=nested-1.x nested-2.x nested-3.x pipeline.x

all: $(BIN)

nested-1.x: nested-1.c
	gcc $^ -Wall -fopenmp -o $@

nested-2.x: nested-2.c
	gcc $^ -Wall -fopenmp -o $@

nested-3.x: nested-3.c
	gcc $^ -Wall -fopenmp -o $@

pipeline.x: pipeline.c
	gcc $^ -fopenmp -o $@

clean:
	rm -f *.x
