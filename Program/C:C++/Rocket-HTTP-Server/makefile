httpd : file1.o file2.o file3.o
	gcc file1.o file2.o file3.o -o httpd

file1.o : rocket.c rocket.h
	gcc -c rocket.c -o file1.o

file2.o : rocketSocket.h rocketSocket.c
	gcc -c rocketSocket.c -o file2.o

file3.o : rocketThread.h rocketThread.c
	gcc -c rocketThread.c -o file3.o

clean:
	rm -rf *.o httpd
