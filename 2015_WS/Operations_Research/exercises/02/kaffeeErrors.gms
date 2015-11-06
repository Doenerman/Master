$Title KaffeeMischungen


  Sets
    i   Kaffeebohnen    / Arabica, Robusta, Liberica, Excelsa /
    j   Kaffeesorten    / Fernweh, Excellence, AfricanNight, FeuerBraziliens / ;

  Parameter
    c(i)    Preis je kg Bohnen
      / Arabica 2.50, Robusta 2.10, Liberica 2.90, Excelsa 3.50 /
    b(i)    Verfuegbare kg von Bohne i
      / Arabica 20000, Robusta 12000, Liberica 5000, Excelsa 3000 /
    d(j)    Mindestabsatz Sorte j in kg
      / Fernweh 10000, Excellence 1000, AfricanNight 5000, FeuerBraziliens 6000 /
    p(j)    Verkaufspreis von Sorte j pro kg
      / Fernweh 6.95, Excellence 12, AfricanNight 9, FeuerBraziliens 7.95 /

  Table ao(i,j)     Maximaler Anteil von Bohne i an Sorte j
                Fernweh Excellence  AfricanNight    FeuerBraziliens
    Arabica     0.8     0.3         0.5             1
    Robusta     0.4     0.3         1               0.6
    Liberica    1       0.6         0.2             0.3
    Excelsa     1       1           1               0.2

  Table au(i,j)     Minimaler Anteil von Bohne i an Sorte j
                Fernweh Excellence  AfricanNight    FeuerBraziliens
    Arabica     0.5                 0.3             0.6
    Robusta     0.3                 0.5
    Liberica   0.1     0.3                         0.1
    Excelsa             0.5         0.1                             ;

  Variables
    x(i)    Soviel von Bohne i kaufen
    y(j)    Soviel von Sorte j verkaufen
    z(i,j)  Soviel von Bohne i fuer Sorte j verwenden
    g       Der erzielte Gewinn;

  Positive Variables x,y,z ;

  Equations
      Gewinn                Der erzielte Gewinn
      maxBohnen(i)          Menge verfuegbarer Bohnen nicht ueberschritten
      minSorte(j)           Mindestabsatz einhalten
      BohnenSumme(i)        Genausoviel vermischen wie gekauft
      SortenSumme(j)        Genausoviel absetzen wie gemischt
      minAnteil(i,j)        Mindestanteile einhalten
      maxAnteil(i,j)        maximale Anteile einhalten ;

  Gewinn ..         g =e= sum(j,p(j)*y(j)) - sum(i, c(i)*x(i));
  maxBohnen(i) ..   x(i) =l= b(i);
  minSorte(j) ..    y(j) =g= d(j);
  BohnenSumme(i) .. sum(j, z(i,j)) =e= x(i);
  SortenSumme(j) .. sum(i, z(i,j)) =e= y(j);
  minAnteil(i,j) .. z(i,j) =g= au(i,j) * y(j);
  maxAnteil(i,j) .. z(i,j) =l= ao(i,j) * y(j);

  Model Kaffee / all /;
  Solve Kaffee using lp maximizing g;
  Display x.l, x.m;
