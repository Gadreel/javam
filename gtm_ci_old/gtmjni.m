set(gln,value) ;
	set @gln=value
	quit

get(gln) ;
	quit $get(@gln)	

kill(gln) ;
	kill @gln
	quit

order(gln,direction) ;
	quit $order(@gln,direction)

query(gln) ;
	quit $query(@gln)

increment(gln,expr)
	quit $increment(@gln,expr)

tstart(x)   ;
	;tstart
	quit

tcommit(x)  ;
	;tcommit
	quit
