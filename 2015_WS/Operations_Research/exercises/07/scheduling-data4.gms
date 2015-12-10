$Title scheduling-data4

  Sets
       j   jobs          / j1*j10 /
       t   time          / t1*t110 /;

  alias (i,j);
  alias (t,tt);


  Parameters

	p(j) / j1 1, j2 2, j3 3, j4 4, j5 5, j6 6, j7 7, j8 8, j9 20.5,
		j10 50.5 /
	r(j) / j1 10, j2 2, j3 8, j4 7, j5 6, j6 5, j7 4, j8 3, j9 2,
		j10 1/;


  Set
       prec(i,j)   precedences
       / j1.j2,
         j2.j3,
         j3.j4,
         j4.j5,
         j5.j6,
         j6.j7,
         j8.j9,
         j9.j10/;

  Scalars
       M    big M;
       M =  110 ;
