BIN=02.axpy.x 02d.axpy-omp-for.x \
    03d.pi-omp-red-for.x 03.pi.x \
    11.loop-canonical.x 11.loop-collapse.x 11.loop-datadeps-fib.x 11.loop-ilegal-2.x \
    11.loop-ilegal.x 11.loop-lastprivate.x 11.loop-reduction.x 11.loop-schedule.x 11.loop-worksharing.x \
    12.sections.x 13.master.x 13.single.x 14.worksharing-pitfalls.x

all: $(BIN)

02.axpy.x: 02.axpy.c
	gcc $^ -Wall -o $@

02d.axpy-omp-for.x: 02d.axpy-omp-for.c
	gcc $^ -Wall -fopenmp -o $@

03.pi.x: 03.pi.c
	gcc $^ -Wall -fopenmp -o $@

03d.pi-omp-red-for.x: 03d.pi-omp-red-for.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-canonical.x: 11.loop-canonical.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-collapse.x: 11.loop-collapse.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-datadeps-fib.x: 11.loop-datadeps-fib.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-ilegal-2.x: 11.loop-ilegal-2.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-ilegal.x: 11.loop-ilegal.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-lastprivate.x: 11.loop-lastprivate.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-reduction.x: 11.loop-reduction.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-schedule.x: 11.loop-schedule.c
	gcc $^ -Wall -fopenmp -o $@

11.loop-worksharing.x: 11.loop-worksharing.c
	gcc $^ -Wall -fopenmp -o $@

12.sections.x: 12.sections.c
	gcc $^ -Wall -fopenmp -o $@

13.master.x: 13.master.c
	gcc $^ -Wall -fopenmp -o $@

13.single.x: 13.single.c
	gcc $^ -Wall -fopenmp -o $@

14.worksharing-pitfalls.x: 14.worksharing-pitfalls.c
	gcc $^ -Wall -fopenmp -o $@

clean:
	rm -f $(BIN)
