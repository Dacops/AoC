CFLAGS = -O3 -std=c++23 -Wall -Wextra -Werror
TARGET1 = 1st-part
TARGET2 = 2nd-part
INPUT	= input.txt

all: $(TARGET1).cpp $(TARGET2).cpp
	g++ $(CFLAGS) $(TARGET1).cpp -o $(TARGET1)
	g++ $(CFLAGS) $(TARGET2).cpp -o $(TARGET2)

1: $(TARGET1)
	./$(TARGET1) < $(INPUT)
2: $(TARGET2)
	./$(TARGET2) < $(INPUT)
clear:
	rm -f $(TARGET1) $(TARGET2)

