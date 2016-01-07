$Title santa

* Santa's Stolen Sleigh

$include santa-data1.gms

Variables
        z         objective function variable;

Parameter pi pi;
          pi = 3.141592653589793;

Parameter r radius;
          r = 6378.388;

* Hier das fehlende Modell einfuegen




Model santa / all / ;
santa.optcr=0.0;
Solve santa using mip minimizing z;
