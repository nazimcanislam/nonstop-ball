build:
	rm -rf bin
	mkdir bin
	cp -R res bin/
	g++ -c src/*.cpp -I /usr/include -I include
	g++ -o bin/NonstopBall *.o -L /usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system
	rm *.o
	./bin/NonstopBall
run:
	./bin/NonstopBall
clear:
	rm -rf bin
