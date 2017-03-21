BIN=anti-dep-1.x flow-dep-1.x flow-dep-2.x output-dep-1.x

all: $(BIN)

flow-dep-1.x: flow-dep-1.c
	gcc $^ -Wall -fopenmp -o $@

flow-dep-2.x: flow-dep-2.c
	gcc $^ -Wall -fopenmp -o $@

anti-dep-1.x: anti-dep-1.c
	gcc $^ -Wall -fopenmp -o $@

output-dep-1.x: output-dep-1.c
	gcc $^ -Wall -fopenmp -o $@

clean:
	rm -f $(BIN)
