$Title assignment

$include assignment-data1

  Variables
       z         objective function value ;



************ Fügen Sie hier die weiteren Variablen und Nebenbedingungen ein

  Positive Variables
       x(i,j,k)     Anzahl der Schueler die von i nach j fahren um in k zu kommen;

  Equations
       Kosten                Die Kosten um alle Schueler unterzubringen
       Kapazitaeten(j,k)     Alle Schueler kommen unter
       Unterbringung(i,k)    Alle kommen unter;

       Kosten..              z =e= sum(i,sum(j,d(i,j)*sum(k,x(i,j,k))));
       Kapazitaeten(j,k)..   sum(i,x(i,j,k)) =l= C(j,k);
       Unterbringung(i,k)..  S(i,k) =e= sum(j,x(i,j,k));


  Model assignment / all / ;
  assignment.limcol = 0;
  assignment.limrow = 0;
  assignment.optcr = 0;
  Solve assignment using mip minimizing z ;
  Display x.l ;
