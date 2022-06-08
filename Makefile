
all: sudoku

sudoku: sudoku.o
	$(CC) -o $@ $<  -lstdc++ -lm

sudoku.o: sudoku.cc
	$(CC) -Wall -std=c++11 -o $@ -c $<

.PHONY: test
test: sudoku
	@for f in *.in; do \
		echo '### ' $$f ' ###'; \
		time ./sudoku < $$f; \
		echo; \
	done

clean:
	rm -f *.o sudoku

