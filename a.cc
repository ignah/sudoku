#include <iostream>
#include <string.h>


int sudoku[9][9];

void
print_sudoku()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << sudoku[i][j];
			if ((j % 3) == 2) std::cout << " ";
		}
		std::cout << std::endl;
		if ((i % 3) == 2) std::cout << std::endl;
	}
}


bool
is_ok(int index)
{
	//std::cout << "index: " << index << std::endl;
	//print_sudoku();

	int cnt[10];
	memset(cnt, 0, sizeof(cnt));

	int row = (index / 9 / 3) * 3;

	int i = row + 3;
	for (; row < i; row++) {
		int col = ((index % 9) / 3) * 3;
		int j = col + 3;
		for (; col < j; col++) {
			//std::cout << "(R) " << row << ", " << col << ": " << sudoku[row][col] << std::endl;
			if (sudoku[row][col] != 0 && cnt[sudoku[row][col]] == 1) {
				return false;
			}
			++cnt[sudoku[row][col]];
		}
	}

	memset(cnt, 0, sizeof(cnt));
	row = (index / 9);
	for (int j = 0; j < 9; j++) {
		//std::cout << "(H) " << row << ", " << j << ": " << sudoku[row][j] << std::endl;
		if (sudoku[row][j] != 0 && cnt[sudoku[row][j]] == 1) {
			return false;
		}
		++cnt[sudoku[row][j]];
	}

	memset(cnt, 0, sizeof(cnt));
	int col = (index % 9);
	for (int i = 0; i < 9; i++) {
		//std::cout << "(V) " << i << ", " << col << ": " << sudoku[i][col] << std::endl;
		if (sudoku[i][col] != 0 && cnt[sudoku[i][col]] == 1) {
			return false;
		}
		++cnt[sudoku[i][col]];
	}
	return true;
}

bool
solve(int index)
{
	if (index >= 81) return true;

	//std::cout << "index: " << index << std::endl;
	//print_sudoku();

	int row = index / 9;
	int col = index % 9;
	if (sudoku[row][col] == 0) {
		for (int num = 1; num <= 9; num++) {
			sudoku[row][col] = num;
			if (is_ok(index)) {
				//std::cout << "index: " << index << ", is_ok returned true" << std::endl;
				//print_sudoku();
				if (solve(index + 1)) {
					return true;
				}
			}
			else {
				//std::cout << "index: " << index << ", is_ok returned false" << std::endl;
				//print_sudoku();
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
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cin >> sudoku[i][j];
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

