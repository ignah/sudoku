

a.out: a.o
	$(CC) -o $@ $<  -lstdc++

a.o: a.cc
	$(CC) -o $@ -c $<
