$Title scheduling

$include scheduling-data1.gms


  Variables
	z	  objective function value ;

* Im Folgenden das fehlende Modell einfuegen *

  Set
    t(j)  Zeitslots die für Job j genutzt werden

  Boolean Variables
  s(j,t)    Job j startet zum Zeitpunkt t
  x(j,t)    Job j wird zum Zeitpunkt t durchgeführt;
  
  positive Integer

  Equations
    full(j)       Job j wird komplett abgearbeitet
    
    time    Die Zeit die benötigt wird um alle Jobs zu erledigen;




  

  Model scheduling / all / ;
  scheduling.optcr=0.0;

  Solve scheduling using mip minimizing z;
