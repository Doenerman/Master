BIN=03c.pi-omp-manual-red-atomic.x 03c.pi-omp-manual-red-critical.x \
	07.incr-ok.x 07.incr-race.x \
	08a.histogram.x 08b.histogram-critical.x 08c.histogram-atomic.x \
	09.barrier.x 09b.barrier-error.x 09c.barrier-error2.x \
	10a.critical-names.x 10b.atomic-critical.x

all: $(BIN)

03c.pi-omp-manual-red-atomic.x: 03c.pi-omp-manual-red-atomic.c
	gcc $^ -Wall -fopenmp -o $@

03c.pi-omp-manual-red-critical.x: 03c.pi-omp-manual-red-critical.c
	gcc $^ -Wall -fopenmp -o $@

07.incr-race.x: 07.incr-race.c
	gcc $^ -Wall -fopenmp -o $@

07.incr-ok.x: 07.incr-ok.c
	gcc $^ -Wall -fopenmp -o $@

08a.histogram.x: 08a.histogram.c
	gcc $^ -Wall -fopenmp -o $@

08b.histogram-critical.x: 08b.histogram-critical.c
	gcc $^ -Wall -fopenmp -o $@

08c.histogram-atomic.x: 08c.histogram-atomic.c
	gcc $^ -Wall -fopenmp -o $@

09.barrier.x: 09.barrier.c
	gcc $^ -Wall -fopenmp -o $@

09b.barrier-error.x: 09b.barrier-error.c
	gcc $^ -Wall -fopenmp -o $@

09c.barrier-error2.x: 09c.barrier-error2.c
	gcc $^ -Wall -fopenmp -o $@

10a.critical-names.x: 10a.critical-names.c
	gcc $^ -Wall -fopenmp -o $@

10b.atomic-critical.x: 10b.atomic-critical.c
	gcc $^ -Wall -fopenmp -o $@

clean:
	rm -f *.x
