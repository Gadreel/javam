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
increment(gln,expr)
 quit $increment(@gln,expr)
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
func(name,args) ;
 n result
 ;
 i '$d(args)#10 s args=""
 s:args'="" args=$$parse(args)
 ;
 x "s result=$$"_name_$s(args'="":args,1:"")
 ;
 quit result
 ;
 ;
proc(name,args) ;
 i '$d(args)#10 s args=""
 s:args'="" args=$$parse(args)
 ;
 x "d "_name_$s(args'="":args,1:"")
 ;
 quit 
 ;