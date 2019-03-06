CXX = g++
CXXFLAGS = -Wall -std=c99 -ggdb3 -O0
LDFLAGS =  

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = bmp2c

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)