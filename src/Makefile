CC=g++
CFLAGS=-g --std=c++11 -Wall -Werror

all: renderer

renderer: main.o
	$(CC) $(CFLAGS) -o renderer main.o

main.o: main.cpp World.hpp Object3D.hpp Polygon.hpp Vertex3D.hpp \
 Vector3D.hpp Line.hpp Matrix.hpp Camera.hpp Light.hpp Render.hpp \
 image.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f renderer

