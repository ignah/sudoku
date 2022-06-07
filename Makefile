
all: a.out a2.out

a.out: a.o
	$(CC) -o $@ $<  -lstdc++

a.o: a.cc
	$(CC) -o $@ -c $<

a2.out: a2.o
	$(CC) -o $@ $<  -lstdc++

a2.o: a2.cc
	$(CC) -o $@ -c $<
