
#include <iostream>
#include <vector>

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int rows = 0;
int cols = 0;
int U = 0;
std::vector<int> vsudoku;

int
get_avail(int index)
{
	int avail = 0;

	int row = (index / rows / U) * U;
	int i = row + U;
	for (; row < i; row++) {
		int col = ((index % cols) / U) * U;
		int j = col + U;
		for (; col < j; col++) {
			int c = vsudoku.at(row * rows + col);
			if (c != 0) {
				avail |= (0x01 << (c - 1));
			}
		}
	}

	row = (index / rows);
	for (int j = 0; j < cols; j++) {
		int c = vsudoku.at(row * rows + j);
		if (c != 0) {
			avail |= (0x01 << (c - 1));
		}
	}

	int col = (index % cols);
	for (int i = 0; i < rows; i++) {
		int c = vsudoku.at(i * rows + col);
		if (c != 0) {
			avail |= (0x01 << (c - 1));
		}
	}
	return avail;
}

bool
solve(int index)
{
	if (index >= (rows * cols)) return true;
	if (vsudoku.at(index) == 0) {
		int avail = get_avail(index);
		for (int num = 1; num <= (U * U); num++) {
			if (avail & (0x01 << (num - 1))) {
				continue;
			}
			vsudoku[index] = num;
			if (solve(index + 1)) {
				return true;
			}
		}
		vsudoku[index] = 0;
		return false;
	}
	return solve(index + 1);
}

void
input_sudoku()
{
	int col = 0;
	rows = 1;
	do {
		int c;
		do {
			c = getchar();
			if (c == '\n') {
				if (col == 0) {
					continue;
				}
				else if (rows == 1) {
					cols = col;
				}
				else if (cols != col) {
					std::cout << "error, cols=" << cols << ", col=" << col << std::endl;
					exit(1);
				}
				if (rows == cols) {
					U = sqrt(cols);
					return;
				}
				++rows;
				col = 0;
			}
		} while (isspace(c));
		++col;

		if (c >= '0' && c <= '9')
			c = c - '0';
		else if (c >= 'a' && c <= 'g')
			c = c - 'a' + 10;
		else if (c >= 'A' && c <= 'G')
			c = c - 'A' + 10;
		else {
			std::cout << "error, " << char(c) << std::endl;
			exit(1);
		}
		vsudoku.push_back(c);
	} while (true);
}

void
print_sudoku()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int c = vsudoku.at(i * cols + j);
			if (c >= 10) {
				putchar('A' + c - 10);
			}
			else {
				putchar('0' + c);
			}
			if ((j % U) == (U - 1)) std::cout << " ";
		}
		std::cout << std::endl;
		if ((i % U) == (U - 1)) std::cout << std::endl;
	}
}

int
main(int argc, char* argv[])
{
	input_sudoku();
	print_sudoku();

	const char* msg = (solve(0)) ?  "<solved!>" : "<oops!>";
	std::cout << msg << std::endl;
	print_sudoku();
	return 0;
}

