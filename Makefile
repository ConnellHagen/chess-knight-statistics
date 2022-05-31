INCLUDES = -I src/include -L src/lib
CXXFlags = -g -Wall
CXX = g++
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ = DBvisualizer.o Entity.o GUI.o main.o Math.o RenderWindow.o Text.o Tile.o

chess: $(OBJ)	
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBS)
	# g++ -Isrc/include/** -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	-rm */*.class *.class *.json */*.exe *.exe *.o *.out

all: run

run: chess
#javac -cp ".;lib/*" *.java && java Main
	./chess.exe

# javac -cp ".;lib/*" *.java && java Main

.PHONY: all run