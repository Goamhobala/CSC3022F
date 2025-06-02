default:
	g++ -std=c++14 -o findcomp PGMimage.cpp PGMimageProcessor.cpp ConnectedComponent.cpp main.cpp 

run:
	./findcomp -m 2 -f 2 8000 -t 35 -p -w "output.pgm" "birds.pgm"

clean:
	rm ./findcomp ./test

test:
	g++ -std=c++17 -o ./test PGMimageProcessor.cpp TestPGMimageProcessor.cpp ConnectedComponent.cpp PGMimage.cpp TestConnectedComponent.cppg++ -std=c++17 -o ./test PGMimageProcessor.cpp TestPGMimageProcessor.cpp ConnectedComponent.cpp PGMimage.cpp TestConnectedComponent.cpp