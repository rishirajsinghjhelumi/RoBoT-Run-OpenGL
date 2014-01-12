CC = g++
#CFLAGS = -Wall
PROG = robot

SRCS = main.c
LIBS = -lglut -lGL -lGLU -lm

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
