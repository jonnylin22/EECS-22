# Makefile: PhotoLab.c

# variable definitions
CC	= gcc
CFLAGS	= -Wall -std=c11  


# default target
all: PhotoLab PhotoLabTest

# convenience targets
clean:
	rm -f *.o 
	rm -f PhotoLab PhotoLabTest
	rm -f *.ppm
	cp ~eecs22/public/EngPlaza.ppm .
	cp ~eecs22/public/watermark_template.ppm .
	cp ~eecs22/public/border.ppm .
	
run: PhotoLab
	./PhotoLab

test: PhotoLabTest

testrun: PhotoLabTest
	./PhotoLabTest

# compilation rules
PhotoLab: PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o Test.o
	$(CC) $(CFLAGS) -lm PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o Test.o -o PhotoLab

PhotoLabTest: PhotoLabTest.o FileIO.o DIPs.o Advanced.o Test.o Image.o 
	$(CC) $(CFLAGS) -lm PhotoLabTest.o FileIO.o DIPs.o Advanced.o Test.o Image.o -o PhotoLabTest

# Complile object files
FileIO.o: FileIO.c FileIO.h Constants.h
	$(CC) $(CFLAGS) -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	$(CC) $(CFLAGS) -c DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS) -c Advanced.c -o Advanced.o

Image.o: Image.c Image.h Constants.h
	$(CC) $(CFLAGS) -c Image.c -o Image.o

PhotoLab.o: PhotoLab.c Constants.h FileIO.h DIPs.h Advanced.h Image.h Test.h
	$(CC) $(CFLAGS) -c PhotoLab.c -o PhotoLab.o

Test.o: Test.c Test.h Constants.h Image.h FileIO.h DIPs.h Advanced.h
	$(CC) $(CFLAGS) -c Test.c -o Test.o

PhotoLabTest.o: PhotoLab.c Constants.h FileIO.h DIPs.h Advanced.h Image.h Test.h
	$(CC) $(CFLAGS) -DDEBUG -c PhotoLab.c -o PhotoLabTest.o

# EOF Makefile #
