CC=g++
INCLUDE_FLAGS=-I. -lglut -lGLU -lGLEW -lGL -lSOIL -lSDL2 -lSDL2_mixer
DEBUG_FLAGS=-g

OUTPUT_NAME=game

all:  
	$(CC) -o ${OUTPUT_NAME} main.cpp $(INCLUDE_FLAGS) ${DEBUG_FLAGS}

run: all
	./${OUTPUT_NAME}

clean:
	rm ./${OUTPUT_NAME}	
