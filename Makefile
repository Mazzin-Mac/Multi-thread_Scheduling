mts: mts.o train_data_structures.o
	gcc -o mts mts.o train_data_structures.o

mts.o: mts.c
	gcc -c mts.c

train_data_structures.o: train_data_structures.c train_data_structures.h
	gcc -c train_data_structures.c

clean:
	rm -f *.o mts
