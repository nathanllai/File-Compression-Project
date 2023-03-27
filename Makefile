all: test_bstream zap test_pqueue unzap

test_bstream: test_bstream.cc bstream.h
	g++ -Wall -Werror -o test_bstream test_bstream.cc -std=c++11 -pthread -lgtest

zap: zap.cc huffman.h
	g++ -Wall -Werror -o zap zap.cc -std=c++11

test_pqueue: test_pqueue.cc pqueue.h
	g++ -Wall -Werror -o test_pqueue test_pqueue.cc -std=c++11 -pthread -lgtest

unzap: unzap.cc huffman.h
	g++ -Wall -Werror -o unzap unzap.cc -std=c++11

clean:
	rm -f test_bstream zap test_pqueue