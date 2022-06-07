#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


const int R = 4; // 3
const int NROW = R * R;
const int NCOL = R * R;

int sudoku[NROW][NCOL];

void
print_sudoku()
{
	for (int i = 0; i < NROW; i++) {
		for (int j = 0; j < NCOL; j++) {
			if (sudoku[i][j] >= 10) {
				putchar('A' + (sudoku[i][j] - 10));
			}
			else {
				std::cout << sudoku[i][j];
			}
			if ((j % R) == (R-1)) std::cout << " ";
		}
		std::cout << std::endl;
		if ((i % R) == (R-1)) std::cout << std::endl;
	}
}


bool
is_ok(int index)
{
	//std::cout << "index: " << index << std::endl;
	//print_sudoku();

	int cnt[R*R+1];
	memset(cnt, 0, sizeof(cnt));

	int row = (index / NROW / R) * R;

	int i = row + R;
	for (; row < i; row++) {
		int col = ((index % NCOL) / R) * R;
		int j = col + R;
		for (; col < j; col++) {
			//std::cout << "(R) " << row << ", " << col << ": " << sudoku[row][col] << std::endl;
			if (sudoku[row][col] != 0 && cnt[sudoku[row][col]] == 1) {
				return false;
			}
			++cnt[sudoku[row][col]];
		}
	}

	memset(cnt, 0, sizeof(cnt));
	row = (index / NROW);
	for (int j = 0; j < NCOL; j++) {
		//std::cout << "(H) " << row << ", " << j << ": " << sudoku[row][j] << std::endl;
		if (sudoku[row][j] != 0 && cnt[sudoku[row][j]] == 1) {
			return false;
		}
		++cnt[sudoku[row][j]];
	}

	memset(cnt, 0, sizeof(cnt));
	int col = (index % NCOL);
	for (int i = 0; i < NROW; i++) {
		//std::cout << "(V) " << i << ", " << col << ": " << sudoku[i][col] << std::endl;
		if (sudoku[i][col] != 0 && cnt[sudoku[i][col]] == 1) {
			return false;
		}
		++cnt[sudoku[i][col]];
	}
	return true;
}

int
get_avail(int index)
{
	int avail = 0;

	int row = (index / NROW / R) * R;
	int i = row + R;
	for (; row < i; row++) {
		int col = ((index % NCOL) / R) * R;
		int j = col + R;
		for (; col < j; col++) {
			if (sudoku[row][col] != 0) {
				avail |= (0x01 << (sudoku[row][col] - 1));
			}
		}
	}

	row = (index / NROW);
	for (int j = 0; j < NCOL; j++) {
		if (sudoku[row][j] != 0) {
			avail |= (0x01 << (sudoku[row][j] - 1));
		}
	}

	int col = (index % NCOL);
	for (int i = 0; i < NROW; i++) {
		if (sudoku[i][col] != 0) {
			avail |= (0x01 << (sudoku[i][col] - 1));
		}
	}
	return avail;
}

bool
solve(int index)
{
	if (index >= (NROW * NCOL)) return true;

	//std::cout << "index: " << index << std::endl;
	//print_sudoku();

	int row = index / NROW;
	int col = index % NCOL;
	if (sudoku[row][col] == 0) {
		int avail = get_avail(index);
		for (int num = 1; num <= (R*R); num++) {
			if (avail & (0x01 << (num - 1))) {
				continue;
			}
			sudoku[row][col] = num;
			if (solve(index + 1)) {
				return true;
			}
		}
		sudoku[row][col] = 0;
		return false;
	}
	return solve(index + 1);
}

int
main(int argc, char* argv[])
{
	for (int i = 0; i < NROW; i++) {
		for (int j = 0; j < NCOL; j++) {
			int c;
			//std::cin >> c;
			c = getchar();
			//std::cout << "getchar: " << c << std::endl;
			if (isspace(c)) {
				--j;
				continue;
			}
			if (isdigit(c))
				sudoku[i][j] = c - '0';
			else if (c >= 'a' && c <= 'g')
				sudoku[i][j] = c - 'a' + 10;
			else if (c >= 'A' && c <= 'G')
				sudoku[i][j] = c - 'A' + 10;
			else {
				std::cout << "error, " << c << std::endl;
				exit(1);
			}
		}
	}
	print_sudoku();

	if (solve(0)) {
		std::cout << "<solved!>" << std::endl;
	}
	else {
		std::cout << "<oops!>" << std::endl;
	}
	print_sudoku();

	return 0;
}

