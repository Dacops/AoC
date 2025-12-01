CFLAGS = -O3 -std=c++11 -Wall
TARGET1 = day4-1
TARGET2 = day4-2
INPUT	= input.txt

all: $(TARGET1).cpp $(TARGET2).cpp
	g++ $(CFLAGS) $(TARGET1).cpp -o $(TARGET1)
	g++ $(CFLAGS) $(TARGET2).cpp -o $(TARGET2)

run1: $(TARGET1)
	./$(TARGET1) < $(INPUT)
run2: $(TARGET2)
	./$(TARGET2) < $(INPUT)
clear:
	rm -f $(TARGET1) $(TARGET2)


