CC:=g++
CFLAGS:=-Wall
DIR:=-Iinclude/


all: src/*.cpp
	$(CC) $(DIR) src/*.cpp -o ppm $(CFLAGS)

clean:
	rm -rf doc/ ppm