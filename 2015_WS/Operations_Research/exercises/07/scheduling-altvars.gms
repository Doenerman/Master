$Title scheduling

$include scheduling-data3.gms

  Variables
        cmax      makespan
        x(j,t)    job j starts at time t;

 Binary Variable 
        x(i,t);




  Equations
         makespan                     mimimize makespan
         not_concurrent1              no two jobs at the time
         not_concurrent2              no two jobs at the time
         jobs                         each job must be done
         release                      release dates;



  makespan(j,t) ..ord(t) * x(j,t) + p(j) =l= cmax;
  not_concurrent1(i,j,t)$((ord(i)<>ord(j))and(ord(t)<=card(t)-p(j)+1))..
                  1-x(j,t)=g= sum(tt$(ord(tt)>=ord(t)and ord(tt)<=ord(t)+p(j)-1),x(i,tt));
  not_concurrent2(i,j,t)$prec(i,j)..
                  1-x(j,t)=g=sum(tt$((ord(tt)>=ord(t)) and (ord(tt)<=card(t)-p(i)+1)),x(i,tt));
  jobs(j)..       sum(t$((ord(t)>=1) and (ord(t)<=(card(t)-p(j)+1))),x(j,t))=e=1;
  release(j,t)..  ord(t)=g=r(j)*x(j,t);










  Model scheduling / all / ;
  scheduling.optcr=0.0;

  Solve scheduling using mip minimizing cmax;
