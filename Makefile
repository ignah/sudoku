
all: a.out a2.out a3.out

a.out: a.o
	$(CC) -o $@ $<  -lstdc++

a.o: a.cc
	$(CC) -o $@ -c $<

a2.out: a2.o
	$(CC) -o $@ $<  -lstdc++

a2.o: a2.cc
	$(CC) -o $@ -c $<

a3.out: a3.o
	$(CC) -o $@ $<  -lstdc++

a3.o: a3.cc
	$(CC) -o $@ -c $<
