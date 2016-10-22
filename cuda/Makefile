# Makefile for OpenGL/GLUT programs.

# Author: John M. Weiss, Ph.D.
# Written Fall 2016 for CSC433/533 Computer Graphics.

# Usage:  make target1 target2 ...

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = nvcc
CU = nvcc

# Turn on optimization and warnings (add -g for debugging with gdb):
# CPPFLAGS = 		# preprocessor flags
CFLAGS = -O -Wall
CXXFLAGS = -O -Wall -std=c++11 -g
NVCCFlAGS = -O -Wall -std=c++11 -g

# OpenGL/Mesa libraries for Linux:
GL_LIBS = -lglut -lGLU -lGL -lm

# OpenGL libraries for Windows (MinGW):
# GL_LIBS = -lfreeglut -lglu32 -lopengl32
# GL_LIBS = -lglut32 -lglu32 -lopengl32

# OpenGL libraries for Windows (MSVS):
# GL_LIBS = opengl32.lib glu32.lib freeglut.lib
# GL_LIBS = opengl32.lib glu32.lib glut32.lib

#-----------------------------------------------------------------------

# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:    Fractals

# specific targets
Fractals:	Fractals.o Util.o Julia.o  Mandel.o Colors.o
	$(LINK) -o $@ $^ $(GL_LIBS) $(NVCCFLAGS)

Mandel.o:
	nvcc -c Mandel.cu -std=c++11 -g

# generic C and C++ targets for OpenGL programs consisting of only one file
# type "make filename" (no extension) to build
.c:
	$(CC) -o $@ $@.c $(CFLAGS) $(GL_LIBS)

.cpp:
	$(CXX) -o $@ $@.cpp $(CXXFLAGS) $(GL_LIBS)

.cu:
	$(CU) -o $@ $@.cu $(CXXFLAGS) $(GL_LIBS)

# utility targets
clean:
	rm -f *.o *~ core
