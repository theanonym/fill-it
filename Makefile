TARGET = main
CXX = g++
CXXFLAGS = -O3 `sdl-config --cflags`
LIBS = `sdl-config --libs` -lSDL_ttf -lSDL_image

all:
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o
	$(CXX) $(CXXFLAGS) -c src/app.cpp -o app.o
	$(CXX) $(CXXFLAGS) -c src/yobadraw.cpp -o yobadraw.o
	$(CXX) $(LIBS) main.o app.o yobadraw.o -o $(TARGET)
   
clean:
	rm -f ./*.o
