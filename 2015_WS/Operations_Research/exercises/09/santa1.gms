$Title santa

* Santa's Stolen Sleigh

$include santa-data3.gms

Variables
        z         objective function variable
        a
        t(i)      Zeitpunkt wann i besucht wird
        x(i,j)    binärvariable;

Binary Variable x;



Parameter pi pi;
          pi = 3.141592653589793;

Parameter r radius;
          r = 6378.388;

Parameter d(i,j) Distanz;
          d(i,j)=2*r*arcsin(sqrt(sqr(sin((lat(j)*pi/180-lat(i)*pi/180)/2)))
                 +cos(lat(i)*pi/180)*cos(lat(j)*pi/180)*
                 sqr(sin((long(j)*pi/180-long(i)*pi/180)/2)));
display d;


Parameter
         M Big M;
         M = smax((i,j),d(i,j));
Display M;

Alias(i,p,k,l)

Equations
*         eq1(i,j) objective value
         eq2(i)
         eq3(j)
         eq4(i,j)
         eq5(i,j)                                ;

*eq1(i,j)$(ord(i)<>ord(j))..z=e=sum(p$(ord(p)=1),w(p))+(sum(k$(ord(k)>=1),
*                         w(k))-sum(l$(ord(l)<=card(p) and(ord(l)>=1)),w(l)));
*eq1(i,j)$(ord(i)<>ord(j))..z=e=sum((k,l),(10+w(k)-w(l)));
*eq1(i,j)$(ord(i)<>ord(j))..z=e=sum(p,10*d(i,j));
*eq1(i,j)$(ord(i)<>ord(j))..z=e=sum(p,(10+sum(k$(ord(k)>=1),w(k))-sum(l,w(l))));
eq2(i)..sum(j$(ord(j)>=1 and ord(j)<>ord(i)),x(i,j))=e=1;
eq3(j)..sum(i$(ord(i)>=1 and ord(i)<>ord(j)),x(i,j))=e=1;
eq4(i,j)$(ord(i)<>ord(j)and ord(j)<>1)..t(i)+d(i,j)=l=t(j)+M*(1-x(i,j));

eq5(i,j)$(ord(i)<>ord(j))..z=e=sum(p$(ord(p)>=1),(10+
                          sum(k$(ord(k)>=1),w(k))
                         -sum(l$(ord(l)<=ord(p)and(ord(l)>=1)),w(l)))
                         *(d(p,p+1)));




Model santa / all / ;
santa.optcr=0.0;

Solve santa using mip minimizing z;
