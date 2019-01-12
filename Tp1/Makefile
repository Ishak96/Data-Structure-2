CC=gcc
LIBS=-lGL -lGLU -lglut  -LGL -lX11 -lX11 -lm
LIBSDIR= -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib


#gcc -o ex1 ex1.c -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib -lglut -lGLU -lGL -lX11 -lm

Graph : Graph.c
	${CC} Graph.c -o Graph ${LIBS} ${LIBSDIR}

clean :
	rm -f Graph *~ \#*\#

