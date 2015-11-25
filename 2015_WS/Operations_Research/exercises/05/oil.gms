$Title oil

$include oilData1.gms

Variables  z   Zielfunktionsvariable ;

* Im Folgenden das fehlende Modell einfuegen *


Model oil / all / ;

oil.optcr  = 0.0;

Solve oil using mip minimizing z;

display x.l;
display y.l;

  

