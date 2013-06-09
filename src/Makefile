CC=g++
CFLAGS=-g -std=c++03 -Wall -Werror

all: renderer

renderer: main.o
	$(CC) $(CFLAGS) -o renderer main.o

main.o: main.cpp World.hpp Object3D.hpp Polygon.hpp Vertex3D.hpp \
 Vector3D.hpp Line.hpp Exception.hpp Matrix.hpp Camera.hpp Render.hpp \
 image.hpp Shader.hpp ShaderGroup.hpp FlatShader.hpp PhongShader.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f renderer

