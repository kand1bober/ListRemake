
CC = g++
CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra


SOURCES_DIR = Sources

SOURCES = $(wildcard $(SOURCES_DIR)/*cpp ) 

OBJECTS = $(SOURCES:.cpp =.o) 

EXECUTABLE = List


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(EXECUTABLE)


%.o: %.cpp
	$(CC) -c $(CFLAGS) -IHeaders$< -o $@


clean:
	@rm  -rf $(SOURCES_PROC/*.o)  $(SOURCES_STACK/*.o)  $(EXECUTABLE) ListGraph.dot ListGraph.svg ListGraph.html
	