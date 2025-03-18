
# Compilar o programa principal
huffman: main.o huffman.o heap.o
	g++ main.o huffman.o heap.o -o huffman

# Compilar o arquivo main.o
main.o: main.cpp huffman.hpp heap.hpp
	g++ -c main.cpp

# Compilar o arquivo huffman.o
huffman.o: huffman.cpp huffman.hpp heap.hpp
	g++ -c huffman.cpp

# Compilar o arquivo heap.o
heap.o: heap.cpp heap.hpp
	g++ -c heap.cpp

# Regra para executar a compressão
exeC: huffman
	./huffman C $(word 2, $(MAKECMDGOALS)) $(word 3, $(MAKECMDGOALS))

val_exeC: huffman
	valgrind ./huffman C $(word 2, $(MAKECMDGOALS)) $(word 3, $(MAKECMDGOALS))

# Regra para executar a descompressão
exeD: huffman
	./huffman D $(word 2, $(MAKECMDGOALS)) $(word 3, $(MAKECMDGOALS))

val_exeD: huffman
	valgrind ./huffman D $(word 2, $(MAKECMDGOALS)) $(word 3, $(MAKECMDGOALS))
# Limpeza dos arquivos de objetos e binário
clean:
	rm -f *.o huffman
	rm -rf $(RESULT_DIR)