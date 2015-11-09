$Title assignment

$include assignment-data1

  Variables
       z         objective function value ;

************ Fügen Sie hier die weiteren Variablen und Nebenbedingungen ein



  Model assignment / all / ;
  assignment.limcol = 0;
  assignment.limrow = 0;
  assignment.optcr = 0;
  Solve assignment using mip minimizing z ;
  Display x.l ;
