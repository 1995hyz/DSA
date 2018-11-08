useDijkstra.exe: useDijkstra.o heap.o hash.o dijkstra.o
	g++ -o useDijkstra.exe useDijkstra.o heap.o hash.o dijkstra.o

useDijkstra.o: useDijkstra.cpp
	g++ -c useDijkstra.cpp 

dijkstra.o: dijkstra.cpp dijkstra.h
	g++ -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug: 
	g++ -g -o useDijkstraDebug.exe useDijkstra.cpp heap.cpp hash.cpp dijkstra.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
