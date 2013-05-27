CC=g++
CFLAGS=-g --std=c++11 -Wall -Werror

all: renderer line_test

renderer: main.cpp Vertex3D.hpp Point3D.hpp Polygon.hpp Vector3D.hpp Object.hpp
	$(CC) $(CFLAGS) main.cpp

line_test: line_test.cpp Vertex3D.hpp Point3D.hpp Line.hpp Matrix.hpp Vector3D.hpp image.hpp Render.hpp
	$(CC) $(CFLAGS) line_test.cpp

clean:
	rm -f renderer line_test line_test.tga

