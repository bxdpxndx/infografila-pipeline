CC=g++
CFLAGS=-g --std=c++11 -Wall -Werror

all: renderer line_test poly_test

renderer: main.cpp Vertex3D.hpp Polygon.hpp Vector3D.hpp Object.hpp
	$(CC) $(CFLAGS) -o renderer main.cpp

line_test: line_test.cpp Vertex3D.hpp Line.hpp Matrix.hpp Vector3D.hpp image.hpp Render.hpp Polygon.hpp
	$(CC) $(CFLAGS) -o line_test line_test.cpp

poly_test: Vertex3D.hpp Line.hpp Matrix.hpp Vector3D.hpp image.hpp Render.hpp Polygon.hpp
	$(CC) $(CFLAGS) -o poly_test poly_test.cpp

clean:
	rm -f renderer line_test poly_test line_test.tga poly_test.tga

