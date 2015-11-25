$Title oil

$include oilData3.gms

Variables  
  z   Zielfunktionsvariable ;

Binary Variables
  x(s,o) liefert s an o
  y(s)   s wird gebaut;

Parameter 
  dist(s,o)   Distanz von s nach o;
  dist(s,o) = sqrt( sqr(xcoord(s) - xcoord(o) )  + sqr(ycoord(s) - ycoord(o)) );

Equations
  a(o)        jede Plattform muss einmal benutzt werden
  q(s)        keine Raffiniere darf mehr als zwei mal saugen
  bau(s,o)    muss s gebaut werden
  ziel        Kostenfunktion;

  a(o)..        sum(s,x(s,o))=e=1;
  q(s)..        sum(o, x(s,o))=l=b;
  bau(s,o)..    x(s,o)=l=y(s);
  ziel..        z=e=sum(s, y(s)*f(s) +  sum(o, x(s,o)*c*dist(s,o)));
  


Model oil / all / ;

oil.optcr  = 0.0;

Solve oil using mip minimizing z;

display x.l;
display y.l;
  

