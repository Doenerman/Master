$Title scheduling

$include scheduling-data1.gms

  Variables
	z	  objective function value ;

* Im Folgenden das fehlende Modell einfuegen *




  Model scheduling / all / ;
  scheduling.optcr=0.0;

  Solve scheduling using mip minimizing z;
