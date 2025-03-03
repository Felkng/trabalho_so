huffman: main.o huffman.o
	g++ main.o huffman.o -o huffman

main.o: main.cpp huffman.h
	g++ -c main.cpp

huffman.o: huffman.cpp huffman.h
	g++ -c huffman.cpp

clean:
	rm -f *.o huffman