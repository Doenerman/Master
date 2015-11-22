$Title oil-Data1

$eolcom # 
Sets
      p    alle standorte / o1*o6,
	                    s1*s6 /
      o(p) Oelfaelder / o1*o6 /
      s(p) potentielle Standorte der Raffinerien / s1*s6 /;

Alias(p,pp);


Parameter xcoord(p) x-Koordinate

	  / s1 135
	    s2 359
	    s3 30
	    s4 332
	    s5 48
	    s6 165 
	    o1 81
	    o2 120
	    o3 200
	    o4 236 
	    o5 340 
	    o6 439 / ;



Parameter ycoord(p) y-Koordinate

	  / s1 32
	    s2 121
	    s3 350
	    s4 302
	    s5 133
	    s6 96 
	    o1 74
	    o2 159
	    o3 38
	    o4 124 
	    o5 50 
	    o6 88 / ;

Parameter f(s) Errichtungskosten
	  / s1 100
	    s2 120 
	    s3 110
	    s4 90
	    s5 80
	    s6 100 / ;


Scalar c Kostenkoeffizient fuer die Anbindungskosten / 2.5 /;


Scalar b Maximale Anzahl Oelfelder pro Raffinerie / 3 /;
