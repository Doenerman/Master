$Title oil-Data1

$eolcom # 
Sets
      p    alle standorte / o1*o4,
	                    s1*s4 /
      o(p) Oelfaelder / o1*o4 /
      s(p) potentielle Standorte der Raffinerien / s1*s4 /;

Alias(p,pp);


Parameter xcoord(p) x-Koordinate

	  / s1 135
	    s2 359
	    s3 30
	    s4 332
	    o1 81
	    o2 120
	    o3 200
	    o4 236 / ;



Parameter ycoord(p) y-Koordinate

	  / s1 32
	    s2 121
	    s3 350
	    s4 302
	    o1 74
	    o2 159
	    o3 38
	    o4 124 / ;

Parameter f(s) Errichtungskosten
	  / s1 100
	    s2 120 
	    s3 110
	    s4 90 / ;


Scalar c Kostenkoeffizient fuer die Anbindungskosten / 3.5 /;


Scalar b Maximale Anzahl Oelfelder pro Raffinerie / 2 /;
