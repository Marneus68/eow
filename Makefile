TARGET  := eow
WARN    := -Wall
OFLAGS  := 
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CC      := g++

C_SRCS      = $(wildcard *.cpp)
OBJ_FILES   = $(C_SRCS:.cpp=.o)

%o: %cpp
	@echo "Compiling "$<"..."
	$(CC) -c $(OFLAGS) $< -o $@

$(TARGET): $(OBJ_FILES)
	@echo "Linking..."
	$(CC) $(OFLAGS) -o $@ $(OBJ_FILES) $(LDFLAGS)
	@echo "Done."

# Specific rule for the sound manager. DO NOT OPTIMIZE WITH -OX
#Soundman.o: Soundman.cpp
#	@echo "Compiling the music manager..."
#	$(CC) -c $< -o $@

all: ${TARGET}

clean:
	@echo "Cleaning..."
	rm -rf *.o

mrproper: clean
	rm -rf ${TARGET}

