$title Zero-One-Knapsack Assignment with capacity constraints

$include ckp-data1.gms

Variables z total profit;

************ Fügen Sie hier die weiteren Variablen und Nebenbedingungen ein

  Binary Variables
    x(i)  wahr, genau dann wenn der Gegenstand i eingepackt wird;
  
  Equations
    Profit          Der gesamte erzielte Profit im Sack
    mindestAnzahl   Die minimale Anzahl an Gegenständen im Rucksack
    maxAnzahl       Die maximale Anzahl an Gegenständen im Rucksack
    Capacity        Beschränkung der Inhalte auf die maximale Kapazität des Rucksacks;

    Profit ..       z=e=sum(i, x(i)*p(i));
    mindestAnzahl.. l =l= sum(i, x(i));
    maxAnzahl..     u =g= sum(i, x(i));
    Capacity..      b =g= sum(i, x(i)*a(i));






************ Sorgt dafuer, dass alle Nebenbedingungen in das Modell integriert wird
************ und dann gelöst wird.

Model knapsack /all/ ;
knapsack.limCol = 0;
knapsack.limRow = 0;
solve knapsack using mip maximizing z ;



