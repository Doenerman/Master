$Title scheduling-data1

  Sets
       j   jobs          / j1*j10 /
       t   time          / t1*t85 /;

  alias (i,j);
  alias (t,tt);


  Parameters
	p(j) job duration
        / j1 6, j2 2, j3 4, j4 9, j5 8, j6 3, j7 2, j8 8, j9 12, j10 8 /
	r(j) release date
        / j1 9, j2 15, j3 5, j4 23, j5 13, j6 3, j7 9, j8 17, j9 18, j10 4/;


  Set
       prec(i,j)   precedences
       / j1.j4,
         j4.j9,
         j8.j5,
         j10.j3,
         j9.j6,
         j7.j6,
         j3.j6 / ;

  Scalars
       M    big M;
       M =  85 ;
