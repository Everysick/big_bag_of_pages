TARGET = ../bin/bibop
CFLAGS = -g -Wall
SRCS = bibop.cc

all :
	mkdir -p "$$(dirname $(TARGET))"
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean :
	rm -f *.d *.o $(TARGET)

.PHONY : all clean
