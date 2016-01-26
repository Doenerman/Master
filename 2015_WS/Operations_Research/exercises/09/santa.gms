$Title santa

* Santa's Stolen Sleigh

$include santa-data2.gms

Alias(i,p);
Variables
        z         objective function variable
        y(i)      Distance until place i
        ;


Binary Variables
        x(i,j)    Travel from i to j
        ;


Parameter pi pi;
          pi = 3.141592653589793;

Parameter r radius;
          r = 6378.388;

Parameter
        d(i,j)    Distance between i and j;
        d(i,j)= 2*r*  arcsin(
                    sqrt(
                      sqr(
                        sin((lat(j)-lat(i))/(2))
                      )
                      +
                      cos(lat(i))*cos(lat(j))*
                      sqr(
                        sin((long(j)-long(i))/2)
                      )
                    )
                  );


Scalars
          M   big M;
          M = sum(i, sum(j, d(i,j)));


* Hier das fehlende Modell einfuegen

Equations
        travelDist  The traveled distance
        travelI     Every place must be entered once
        travelO     Every place must be left once
        objective   Dieses Rentierding halt
        eq          roflcopter
        ;

travelDist(i,j)$(ord(i)<>ord(j))..
  y(i)+d(i,j) =l= y(j)+M*(1-x(i,j));
travelI(i)..  1 =e= sum(j$(ord(i)<>ord(j) and ord(j)>=1), x(i,j));
travelO(j)..  1 =e= sum(i$(ord(i)<>ord(j) and ord(i)>=1), x(i,j));

objective..   z =e=sum(i,
                    w(i)*y(i)
                  )
                  + 10 *
                  sum(i,
                    sum(j$(ord(i)<>ord(j)), x(i,j)*d(i,j))
                  )
                  ;
eq(i).. y(i) =g= 0;





Model santa / all / ;
santa.optcr=0.0;
Display d;
Solve santa using mip minimizing z;
