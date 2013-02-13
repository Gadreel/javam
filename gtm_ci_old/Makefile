
all: libgtm_ci.so

libgtm_ci.so: gtmci.c
	gcc -c -m32 -g -O2 gtmci.c -I/usr/java/jdk1.6/include -I/usr/java/jdk1.6/include/linux -I/opt/gtm
	gcc -m32 -shared -o libgtm_ci.so gtmci.o -L/opt/gtm -lgtmshr

clean:	
	rm -f *.o
	rm -f libgtm_ci.so
