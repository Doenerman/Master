$Title santa

* Santa's Stolen Sleigh

$include santa-data3.gms

Variables
        z         objective function variable
        t(i)      distance until i
        x(i,j)    is connection from i to j used;

Binary Variable x;

Positive Variable t;

Parameter pi pi;
          pi = 3.141592653589793;

Parameter r radius;
          r = 6378.388;

Parameter latpi(i) lat in Rad;
          latpi(i)= lat(i)*pi/180;
Parameter longpi(i) long in Rad;
          longpi(i)= long(i)*pi/180;

Parameter d(i,j) distance between i and j;
          d(i,j)=2*r*arcsin(sqrt(sqr(sin(((latpi(j)-latpi(i))/2)))+cos(latpi(i))*cos(latpi(j))*sqr(sin(((longpi(j)-longpi(i))/2)))));
display d;

Parameter
         M Big M;
         M = smax((i,j),d(i,j))*card(i);
Display M;

Alias(i,p,k,l)

Equations
         eq1 objective value
         in(i)     tour requierment
         out(j)    tour requierment
         dist(i,j) update distances; 

eq1..z=e=sum(p,w(p)*t(p))+sum((l,k)$(ord(l)<>ord(k)),d(l,k)*x(l,k))*10;
in(i)..sum(j$(ord(j)>=1 and ord(j)<>ord(i)),x(i,j))=e=1;
out(j)..sum(i$(ord(i)>=1 and ord(j)<>ord(i)),x(i,j))=e=1;
dist(i,j)$(ord(i)<>ord(j)and ord(j)<>1)..t(i)+d(i,j)=l=t(j)+M*(1-x(i,j));



Model santa / all / ;
santa.optcr=0.0;

Solve santa using mip minimizing z;
