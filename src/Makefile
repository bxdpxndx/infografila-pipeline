CC=g++
CFLAGS=-g -O2 -std=c++03 -Wall -Werror

all: renderer

renderer: main.cpp World.hpp Object3D.hpp Polygon.hpp Vertex3D.hpp \
 Vector3D.hpp Line.hpp Exception.hpp Matrix.hpp Camera.hpp Render.hpp \
 image.hpp Shader.hpp ShaderGroup.hpp FlatShader.hpp Poly_borders.hpp \
 Utils.hpp PhongShader.hpp

	$(CC) $(CFLAGS) -o renderer main.cpp

clean:
	rm -f renderer

