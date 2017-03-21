BIN=01.hello_world.x 01b.hello_world-omp.x 01c.hello_world-omp-v2.x \
	01d.hello_world-omp-v3.x 01e.hello_world-omp-v4.x \
	02.axpy.x 02b.axpy-omp.x 02c.axpy-omp-v2.x \
	03.pi.x 03b.pi-omp.x 03c.pi-omp-manual-red.x 03d.pi-omp-red.x \
	04.parallel-data-sharing.x 04.parallel-if.x 04.parallel-reduction.x \
	05a.reduction-max-sequential.x 05b.reduction-max-userdefined.x \
	06a.private-struct.x 06b.private-array.x 06c.private-pointer.x

all: $(BIN)

01.hello_world.x: 01.hello_world.c
	gcc $^ -Wall -o $@

01b.hello_world-omp.x: 01b.hello_world-omp.c
	gcc $^ -Wall -fopenmp -o $@

01c.hello_world-omp-v2.x: 01c.hello_world-omp-v2.c
	gcc $^ -Wall -fopenmp -o $@

01d.hello_world-omp-v3.x: 01d.hello_world-omp-v3.c
	gcc $^ -Wall -fopenmp -o $@

01e.hello_world-omp-v4.x: 01e.hello_world-omp-v4.c
	gcc $^ -Wall -fopenmp -o $@

02.axpy.x: 02.axpy.c
	gcc 02.axpy.c -Wall -fopenmp -o 02.axpy.x

02b.axpy-omp.x: 02b.axpy-omp.c
	gcc 02b.axpy.c -Wall -fopenmp -o 02b.axpy.x

02c.axpy-omp-v2.x: 02c.axpy-omp-v2.c
	gcc $^ -Wall -fopenmp -o $@

03.pi.x: 03.pi.c
	gcc -fopenmp 03.pi.c -Wall -o 03.pi.x

03b.pi-omp.x: 03b.pi-omp.c
	gcc $^ -Wall -fopenmp -o $@

03c.pi-omp-manual-red.x: 03c.pi-omp-manual-red.c
	gcc $^ -Wall -fopenmp -o $@

03d.pi-omp-red.x: 03d.pi-omp-red.c
	gcc $^ -Wall -fopenmp -o $@

04.parallel-if.x: 04.parallel-if.c
	gcc $^ -Wall -fopenmp -o $@

04.parallel-data-sharing.x: 04.parallel-data-sharing.c
	gcc $^ -Wall -fopenmp -o $@

04.parallel-reduction.x: 04.parallel-reduction.c
	gcc $^ -Wall -fopenmp -o $@

05a.reduction-max-sequential.x: 05a.reduction-max-sequential.c
	gcc $^ -Wall -fopenmp -o $@

05b.reduction-max-userdefined.x: 05b.reduction-max-userdefined.c
	gcc $^ -Wall -fopenmp -o $@

06a.private-struct.x: 06a.private-struct.c
	gcc $^ -Wall -fopenmp -o $@

06b.private-array.x: 06b.private-array.c
	gcc $^ -Wall -fopenmp -o $@

06c.private-pointer.x: 06c.private-pointer.c
	gcc $^ -Wall -fopenmp -o $@

clean:
	rm -f $(BIN)
