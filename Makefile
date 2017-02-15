data: data.o main.o
	g++ -std=c++11 -Wall -W -pedantic -Werror data.cpp main.cpp -o data

clean:
	rm -f data data.o main.o
