OBJECTS = ball.o capture.o main.o paddle.o tracker.o


all: bqtest


bqtest: $(OBJECTS)
	g++ -o bqtest $(OBJECTS) -lopencv_core -lopencv_highgui -lopencv_imgproc
