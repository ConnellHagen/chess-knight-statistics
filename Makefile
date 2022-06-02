INCLUDES = -I src/include -L src/lib
CXXFlags = -g -Wall
CXX = g++
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ = DBvisualizer.o Divider.o Entity.o GUI.o main.o Math.o RenderWindow.o Text.o Tile.o utils.o

chess: $(OBJ)	
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	-rm */*.class *.class *.json */*.exe *.exe *.o *.out

all: run

run: chess
# javac -cp ".;lib/*" *.java && java Main
	./chess.exe

.PHONY: all run