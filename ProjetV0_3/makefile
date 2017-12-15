MAIN = main.cpp

HYPER = src/Hyperboloide.cpp
BASE = src/BaseVBO.cpp
FIELD = src/Field.cpp
OBSTACLE = src/Obstacle.cpp
PART = src/Particle.cpp
POINT = src/Point.cpp
VOXEL = src/Voxel.cpp

BIBLIO = -lGL -lGLU -lGLEW -lglut -lm

comp: $(HYPER) $(BASE) $(FIELD) $(OBSTACLE) $(PART) $(POINT) $(VOXEL)
	g++ -Iinclude/ $(HYPER) $(BASE) $(FIELD) $(OBSTACLE) $(PART) $(POINT) $(VOXEL) $(MAIN) -o projet.o $(BIBLIO)
	chmod 700 projet.o

test: src/TestPoint.cpp
	g++ src/TestPoint.cpp -o test.o $(BIBLIO)
	chmod 700 test.o

all: comp
