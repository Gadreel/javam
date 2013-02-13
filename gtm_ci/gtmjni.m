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
 quit $order(@gln,direction)
 ;
query(gln) ;
 quit $query(@gln)
 ;
increment(gln,amt)
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
func(name,args) n code,result  s code="s result=$$"_name_args
 x code
 quit result
 ;
 ;
proc(name,args) n code  s code="d "_name_args
 x code
 quit 
 ;
 ;
echo(a) quit a
 ;
ping(a) w !,"pinged"  quit 
 ;
 ;
