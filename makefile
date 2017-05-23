# makefile for enVR

CC = g++ --std=c++11
XFLAGS = -Wall

# External libraries.
LIBGL = -lGL -lGLU -lglut
LIBCV = `pkg-config --libs opencv`
LFLAGS = $(LIBGL) $(LIBCV) -L./lib

IFLAGS = -I./include

# External headers.
CVINC = `pkg-config --cflags opencv`
CFLAGS = $(IFLAGS) -c

# Header for Constants.
CONSTS = include/enVRConsts.hpp

# Object files.
OBJS = lib/Capture.o lib/Generate.o lib/Viewer.o

enVR : src/main.cpp $(OBJS)
	$(CC) $(XFLAGS) src/main.cpp $(LFLAGS) $(IFLAGS) -o enVR 

lib/Capture.o : lib/Capture.cpp include/Capture.hpp $(CONSTS)
	$(CC) $(XFLAGS) $(CFLAGS) $(CVINC) lib/Capture.cpp -o lib/Capture.o

lib/Generate.o : lib/Generate.cpp include/Generate.hpp $(CONSTS)
	$(CC) $(XFLAGS) $(CFLAGS) $(CVINC) lib/Generate.cpp -o lib/Generate.o

lib/Viewer.o : lib/Viewer.cpp include/Viewer.hpp $(CONSTS)
	$(CC) $(XFLAGS) $(CFLAGS) lib/Viewer.cpp -o lib/Viewer.o
