PROGRAM = SurviveBall
CC      = g++
LDLIBS  = -lglut -lGLU -lGL -lm
ADDFILES = image.cpp 
ADDLIBS = Classes.h Constansts.h image.h Variables.h

$(PROGRAM): Main.o 
	$(CC) $(LDFLAGS) -o $(PROGRAM) $(ADDFILES) $(ADDLIBS) Main.o  $(LDLIBS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)