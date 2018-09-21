spellcheck.out: spellcheck.o hash.o
	g++ -o spellcheck spellcheck.o hash.o
spellcheck.o: spellcheck.cpp hash.h
	g++ -c spellcheck.cpp
hash.o: hash.cpp hash.h
	g++ -c hash.cpp
debug:
	g++ -g -o spellcheckDebug.out spellcheck.cpp hash.cpp
clean:
	rm -f *.out *.o *.stackdump *~
backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
