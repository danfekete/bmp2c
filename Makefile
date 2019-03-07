CXX = gcc
CXXFLAGS = -Wall -std=c99 -g -O0 -c
LDFLAGS =  

SRC = $(wildcard src/*.c)
SRC += argparse/argparse.c
OBJ = $(SRC:.c=.o)
EXEC = bmp2c

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

%.o: %.c
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(OBJ) $(EXEC)