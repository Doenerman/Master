$Title binpacking-data1

Sets
    i   items   / i1*i15 /
    j   bins    / j1*j15 / ;

Alias (i,i_1,i_2);

Sets
    conflict(i_1,i_2) conflicts between two items
	  / i1.i2
	    i1.i4
	    i1.i6
	    i1.i8
	    i1.i10
	    i1.i12
	    i3.i2
	    i3.i4
	    i3.i6
	    i3.i8
	    i3.i10
	    i3.i12
	    i5.i2
	    i5.i4
	    i5.i6
	    i5.i8
	    i5.i10
	    i5.i12
	    i7.i2
	    i7.i4
	    i7.i6
	    i7.i8
	    i7.i10
	    i7.i12
	    i9.i2
	    i9.i4
	    i9.i6
	    i9.i8
	    i9.i10
	    i9.i12
	    i11.i2
	    i11.i4
	    i11.i6
	    i11.i8
	    i11.i10
	    i11.i12
	    /;


Scalar b / 20 / ;

Parameter   a(i)   weights per item
                   / 
                     i1 16
		     i2 4
                     i3 16
                     i4 4
                     i5 16
                     i6 4
                     i7 16
                     i8 4
                     i9 16
                     i10 4
		     i11 4
		     i12 16
		     i13 5
		     i14 7
		     i15 8
		     / ;
