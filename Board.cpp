#include "Board.h"

using namespace std;


void Board::DrawNumber(int count)
{
	srand(time(NULL));

	int i = 0;

	if (i == count) {
		return;
	}

	while (i < count) {
		const int randX = (std::rand() % 9);
		const int randY = (std::rand() % 9);
		const int randNr = (std::rand() % 9) + 1;

		if (IsSafe(randX, randY, randNr)) {
			PlayBoard[randX][randY] = randNr;
			++i;
		}
	}


}

bool Board::IsSafe(int row, int col, int num) 
{
	//sprawdzenie czy w wylosowanym miejscu nie ma juz liczby
	if (PlayBoard[row][col] != 0) {
		return false;
	}

	// sprawdzenie czy w wylosowanym rzedzie nie ma juz liczby
	for (int i = 0; i < 9; ++i) {
		if (PlayBoard[row][i] == num) {
			return false;
		}

		// sprawdzenie czy w wylosowanej linii nie ma juz liczby
		if (PlayBoard[i][col] == num) {
			return false;
		}
	}

	// sprawdzenie czy w wylosowanym obszarze 3 na 3 nie ma juz liczby

	//obliczenie miejsca gdzie zaczyna sie obszar 3x3
	int startRow = row - row % 3;
	int startCol = col - col % 3;

	for (int i = startRow; i < startRow + 3; i++) {
		for (int j = startCol; j < startCol + 3; j++) {
			if (PlayBoard[i][j] == num)
				return false;
		}
	}



	return true;
}

bool Board::IsCorrect(int x, int y, int num)
{
	if (DoneBoard[x][y] == num and PlayBoard[x][y] == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Board::FindUnassignedLocation(int& row, int& col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (PlayBoard[row][col] == 0)
				return true;
	return false;
}

void Board::Clear() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			PlayBoard[i][j] = 0;
			DoneBoard[i][j] = 0;
		}
	}
}

void Board::Insert(int row, int col, int num)
{
	PlayBoard[row][col] = num;
}

int Board::Retrive(int row, int col, int boardNr)
{
	if (boardNr == 0) {
		return PlayBoard[row][col];
	}
	else {
		return DoneBoard[row][col];
	}

}

bool Board::IsDeletable(int x, int y)
{
	int numer = PlayBoard[x][y];

	if (Liczby[numer - 1] > 0) {
		Liczby[numer - 1]--;
		return true;
	}
	else {
		return false;
	}
}

int(&Board::GetTable())[9][9]{
	return PlayBoard;
}

void Board::Play(int poziomTrud)
{
	srand(time(NULL));


	int NumberOfDeletes;

	Clear();
	DrawNumber(5);
	SudokuSolver(PlayBoard);

	for (int j = 0; j < 9; j++) {
		for (int k = 0; k < 9; k++) {
			DoneBoard[j][k] = PlayBoard[j][k];
		}
	}

	int MisteriouslyChangingInt = DoneBoard[8][8];

	switch (poziomTrud) {
	case 1:
		NumberOfDeletes = 25;
		break;
	case 2:
		NumberOfDeletes = 35;
		break;
	case 3:
		NumberOfDeletes = 60;
		break;
	default:
		NumberOfDeletes = 25;
		break;
	}


	int licznik = 0;
	while (licznik < NumberOfDeletes) {
		int randX = (std::rand() % 9);
		int randY = (std::rand() % 9);
		if (IsDeletable(randX, randY)) {
			PlayBoard[randX][randY] = 0;
			licznik++;
		}
	}

	DoneBoard[8][8] = MisteriouslyChangingInt;
}

bool Board::SolveInput()
{
	bool wyn = SudokuSolver(PlayBoard);

	return wyn;
}

bool Board::SudokuSolver(int Table[9][9])
{
	int row, col;
	if (!FindUnassignedLocation(row, col))
		// jeśli nie znaleziono pustego miejsca, sukces
		return true;

	for (int num = 1; num <= 9; num++)
	{

		// Jeżeli na i
		if (IsSafe(row, col, num))
		{
			Table[row][col] = num;
			if (SudokuSolver(Table))
				return true;

			Table[row][col] = 0;
		}
	}

	for (int i = 0; i < 9; i++) {
		Liczby[i] = 9;
	}
	return false;
}