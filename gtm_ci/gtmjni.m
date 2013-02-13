 ;
set(gln,value) ;
 set @gln=value
 quit
 ;
get(gln) ;
 quit $get(@gln)	
 ;
kill(gln) ;
 kill @gln
 quit
 ;
order(gln,direction) ;
 w !,"$o: "_gln_" - "_direction
 quit $order(@gln,direction)
 ;
query(gln) ;
 quit $query(@gln)
 ;
increment(gln,amt)
 w !,"$i: "_gln_" - "_amt
 quit $increment(@gln,amt)
 ;
tstart(x)   ;
 ;tstart
 quit
 ;
tcommit(x)  ;
 ;tcommit
 quit
 ;
trollback(x)  ;
 ;trollback
 quit
 ;
 ;
data(gln) ;
 n x  s x=$data(@gln)	
 w !,"$d: "_gln_" - "_x
 quit $s(x=0:"ff",x=1:"ft",x=10:"tf",1:"tt")
 ;
merge(dest,src) ;
 merge @dest=@src
 quit
 ;
lock(gln) ;
 lock @("+"_gln)
 quit
 ;
unlock(gln) ;
 lock @("-"_gln)
 quit
 ;
func(name,args) ;
 n result
 w !,"s result=$$"_name_args
 x "s result=$$"_name_args
 quit result
 ;
 ;
proc(name,args) ;
 w !,"d "_name_args
 x "d "_name_args
 quit 
 ;
 ;
echo(a) q a
 ;
ping(a) q 
 ;
 ;