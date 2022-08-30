App2.exe: main.o tcpserverwork.o InputCalcFn.o
	g++ main.o tcpserverwork.o InputCalcFn.o -o App2.exe -lpthread
main.o:main.cpp 
	g++ main.cpp -c
tcpserverwork.o:tcpserverwork.cpp 
	g++ tcpserverwork.cpp -c
InputCalcFn.o: InputCalcFn.cpp
	g++ InputCalcFn.cpp -c
clean:
	rm -rf *.o App2.exe