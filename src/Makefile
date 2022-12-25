CC = g++

CFLAGS = -g -Wall -std=c++11

SAVE = save

all:layer save append bcrush vol delay schroeder open


$(SAVE): % : %.o
	$(CC) $(CFLAGS) -o $@ $^

save.o:save.cpp
	g++ $(CFLAGS) -c save.cpp

open:open.o
	g++ $(CFLAGS) -o open open.o

open.o:open.cpp
	g++ $(CFLAGS) -c open.cpp

schroeder:schroeder.o
	g++ $(CFLAGS) -o schroeder schroeder.o

schroeder.o:schroeder.cpp
	g++ $(CFLAGS) -c schroeder.cpp

vol:vol.o
	g++ $(CFLAGS) -o vol vol.o

vol.o:vol.cpp
	g++ $(CFLAGS) -c vol.cpp

delay:delay.o
	g++ $(CFLAGS) -o delay delay.o

delay.o:delay.cpp
	g++ $(CFLAGS) -c delay.cpp

printInfo:printInfo.o
	g++ $(CFLAGS) -o printInfo printInfo.o

printInfo.o:printInfo.cpp
	g++ $(CFLAGS) -c printInfo.cpp

bcrush:bcrush.o
	g++ $(CFLAGS) -o bcrush bcrush.o

bcrush.o:bcrush.cpp
	g++ $(CFLAGS) -c bcrush.cpp

layer:layer.o
	g++ $(CFLAGS) -o layer layer.o

layer.o:layer.cpp
	g++ $(CFLAGS) -c layer.cpp

append:append.o
	g++ $(CFLAGS) -o append append.o

append.o:append.cpp
	g++ $(CFLAGS) -c append.cpp

clean:
	a.out layer append *.o
