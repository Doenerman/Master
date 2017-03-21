BIN=01a.linked-list.x 01b.linked-list-tasks.x \
	02a.fibonacci-rec.x 02b.fibonacci-rec-tasks.x \
	03a.fibonacci-iter.x 03b.fibonacci-iter-reversed-loop.x

all: $(BIN)

01a.linked-list.x: 01a.linked-list.c
	gcc $^ -Wall -fopenmp -o $@

01b.linked-list-tasks.x: 01b.linked-list-tasks.c
	gcc $^ -Wall -fopenmp -o $@

02a.fibonacci-rec.x: 02a.fibonacci-rec.c
	gcc $^ -Wall -fopenmp -o $@

02b.fibonacci-rec-tasks.x: 02b.fibonacci-rec-tasks.c
	gcc $^ -Wall -fopenmp -o $@

03a.fibonacci-iter.x: 03a.fibonacci-iter.c
	gcc $^ -Wall -fopenmp -o $@

03b.fibonacci-iter-reversed-loop.x: 03b.fibonacci-iter-reversed-loop.c
	gcc $^ -Wall -fopenmp -o $@

clean:
	rm -f *.x
