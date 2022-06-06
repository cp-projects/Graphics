test.out:
	make renderer.o
	make vertex_buffer.o
	make index_buffer.o
	make shader.o
	g++ -o test.out learnOpenGl.cpp -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread renderer.o vertex_buffer.o index_buffer.o shader.o /lib64/libGLEW.a

shader.o:
	g++ -c shader.cpp

index_buffer.o:
	g++ -c index_buffer.cpp

vertex_buffer.o:
	g++ -c vertex_buffer.cpp

renderer.o:
	g++ -c renderer.cpp
clean:
	rm ./*.o ./*.out
