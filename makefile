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
OBJS = src/main.o lib/Capture.o lib/Generate.o lib/Viewer.o
INCS = include/Capture.hpp include/Generate.hpp include/Viewer.hpp

enVR : $(OBJS)
	$(CC) $(IFLAGS) $(OBJS) -o enVR $(LFLAGS)

src/main.o : src/main.cpp $(INCS)
	$(CC) $(CFLAGS) src/main.cpp -o src/main.o

lib/Capture.o : lib/Capture.cpp include/Capture.hpp $(CONSTS)
	$(CC) $(CFLAGS) $(CVINC) lib/Capture.cpp -o lib/Capture.o

lib/Generate.o : lib/Generate.cpp include/Generate.hpp $(CONSTS)
	$(CC) $(CFLAGS) $(CVINC) lib/Generate.cpp -o lib/Generate.o

lib/Viewer.o : lib/Viewer.cpp include/Viewer.hpp $(CONSTS)
	$(CC) $(CFLAGS) lib/Viewer.cpp -o lib/Viewer.o

clean:
	rm -f $(OBJS) enVR
