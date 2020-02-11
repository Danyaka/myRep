CC=g++
OPT = -O2
TARGET = app
BROADCAST_UNITS = main.cpp mlib.cpp

all: $(TARGET)

$(TARGET): main.o mlib.o 
	$(CC) $^ -o $@

release: $(BROADCAST_UNITS)
	$(CC) $(OPT) $(BROADCAST_UNITS) -o $(TARGET)_$@

main.o: main.cpp mlib.h
	$(CC) -c $<

mlib.o: mlib.cpp mlib.h
	$(CC) -c $<

clean:
	rm -rf *.o $(TARGET)
