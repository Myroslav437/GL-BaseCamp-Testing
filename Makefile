all: makedir libfs.lib clean
	g++ -fdiagnostics-color=always -std=c++17 -o bin/fsearcher main.cpp -lstdc++fs -pthread bin/libfs.lib

makedir:
	mkdir -p bin
	mkdir -p bin/static

libfs.lib: simplethreadpool.o thrpoolrecsearch.o filesearcher.o
	ar rcs bin/static/libfs.lib bin/static/simplethreadpool.o bin/static/thrpoolrecsearch.o bin/static/filesearcher.o

simplethreadpool.o:
	g++ -std=c++17 -c fsearch/threadpool/simplethreadpool.cpp -o bin/static/simplethreadpool.o -lstdc++fs -pthread

thrpoolrecsearch.o:
	g++ -std=c++17 -c fsearch/thrpoolrecsearch.cpp -o bin/static/thrpoolrecsearch.o -lstdc++fs -pthread

filesearcher.o:
	g++ -std=c++17 -c fsearch/filesearcher.cpp -o bin/static/filesearcher.o -lstdc++fs -pthread

clean:
	mv bin/static/libfs.lib bin
	rm -d -r bin/static