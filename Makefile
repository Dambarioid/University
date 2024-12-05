librational.a: rational.o rat_math.o rat_io.o
	ar -rcs librational.a rational.o rat_math.o rat_io.o

rational.o: rational.c rational.h
	gcc -g -c rational.c

rat_math.o: rat_math.c rational.h
	gcc -g -c rat_math.c

rat_io.o: rat_io.c rational.h
	gcc -g -c rat_io.c
