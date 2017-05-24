# makefile for enVR

CC = g++ --std=c++11

# External libraries.
LIBGL = -lGL -lGLU -lglut
LIBCV = `pkg-config --libs opencv`
LFLAGS = -Wall $(LIBGL) $(LIBCV)

IFLAGS = -I./include

# External headers.
CVINC = `pkg-config --cflags opencv`
CFLAGS = -Wall $(IFLAGS) -c

# Header for Constants.
CONSTS = include/enVRConsts.hpp

# Object files.
OBJS = src/main.o src/Capture.o src/Generate.o src/Viewer.o
INCS = include/Capture.hpp include/Generate.hpp include/Viewer.hpp

enVR : $(OBJS)
	$(CC) $(IFLAGS) $(OBJS) -o enVR $(LFLAGS)

src/main.o : src/main.cpp $(INCS)
	$(CC) $(CFLAGS) src/main.cpp -o src/main.o

src/Capture.o : src/Capture.cpp include/Capture.hpp $(CONSTS)
	$(CC) $(CFLAGS) $(CVINC) src/Capture.cpp -o src/Capture.o

src/Generate.o : src/Generate.cpp include/Generate.hpp $(CONSTS)
	$(CC) $(CFLAGS) $(CVINC) src/Generate.cpp -o src/Generate.o

src/Viewer.o : src/Viewer.cpp include/Viewer.hpp $(CONSTS)
	$(CC) $(CFLAGS) src/Viewer.cpp -o src/Viewer.o

clean:
	rm -f $(OBJS) enVR
