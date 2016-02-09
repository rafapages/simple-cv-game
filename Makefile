OBJECTS = ball.o main.o paddle.o tracker.o


all: cv-simple-game


cv-simple-game: $(OBJECTS)
	g++ -o cv-simple-game $(OBJECTS) -lopencv_core -lopencv_highgui -lopencv_imgproc

clean:
	rm *.o
	rm cv-simple-game
