default:
	make clean
	javac -cp ".;lib/*" *.java && java Main
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 && ./main.exe

clean:
	-rm */*.class *.class *.json *.exe