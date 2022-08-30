App1.exe: main.o app1.o tcpclient.o InputCalcFn.o
	g++ main.o app1.o tcpclient.o InputCalcFn.o -o App1.exe -lpthread
main.o:main.cpp 
	g++ main.cpp -c
app1.o:app1.cpp 
	g++ app1.cpp -c
tcpclient.o: tcpclient.cpp
	g++ tcpclient.cpp -c
InputCalcFn.o: InputCalcFn.cpp
	g++ InputCalcFn.cpp -c
clean:
	rm -rf *.o App1.exe