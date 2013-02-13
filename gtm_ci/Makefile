
all: libgtm_ci.so

libgtm_ci.so: gtmci.c
	gcc -c -m64 -g -O2 -fPIC gtmci.c -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux -I/usr/local/gtm
	gcc -m64 -shared -o libgtm_ci.so gtmci.o -L/usr/local/gtm -lgtmshr

clean:	
	rm -f *.o
	rm -f libgtm_ci.so
