#include "Back.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void back::DrawNumber(int count)
{
    srand(time(NULL));

    int i = 0;

    if (i == count) {
        return;
    }

    while (i < count) {
        int randX = (std::rand() % 9);
        int randY = (std::rand() % 9);
        int randNr = (std::rand() % 9) + 1;

        if (IsSafe(randX, randY, randNr)) {
            Board[randX][randY] = randNr;
            ++i;
        }
    }


}


bool back::IsSafe(int row, int col, int num)
{
    //sprawdzenie czy w wylosowanym miejscu nie ma juz liczby
    if (Board[row][col] != 0) {
        return false;
    }

    // sprawdzenie czy w wylosowanym rzedzie nie ma juz liczby
    for (int i = 0; i < 9; ++i) {
        if (Board[row][i] == num) {
            return false;
        }

        // sprawdzenie czy w wylosowanej linii nie ma juz liczby
        if (Board[i][col] == num) {
            return false;
        }
    }

    // sprawdzenie czy w wylosowanym obszarze 3 na 3 nie ma juz liczby

    //obliczenie miejsca gdzie zaczyna sie obszar 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
             if (Board[i][j] == num)
                 return false;
        }
    }



    return true;
}

bool back::IsCorrect(int x, int y, int num)
{
    if (DoneBoard[x][y] == num and Board[x][y] == 0) {
        return true; 
    }
    else { 
        return false; 
    }
}

bool back::FindUnassignedLocation(int& row, int& col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (Board[row][col] == 0)
                return true;
    return false;
}

void back::Clear() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Board[i][j] = 0;
        }
    }
    return;
}

void back::Insert(int row, int col, int num)
{
    Board[row][col] = num;
}

void back::Delete(int row, int col)
{
    Board[row][col] = 0;
}

int back::Retrive(int row, int col)
{
    return Board[row][col];
}

bool back::IsDeletable(int x, int y)
{
    int numer = Board[x][y];

    if (Liczby[numer - 1] > 0) {
        Liczby[numer - 1]--;
        return true;
    }
    else {
        return false;
    }
}

int(&back::GetTable())[9][9]{
    return Board;
}

int back::Play(int poziomTrud)
{
    srand(time(NULL));
    

    int NumberOfDeletes;
    int i;

    Clear();
    DrawNumber(5);
    SudokuSolver(Board);

    for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 9; k++) {
            DoneBoard[j][k] = Board[j][k];
        }
    }
    int MisteriouslyChangingInt = DoneBoard[8][8];

    switch (poziomTrud) {
    case 1:
        i = 25;
        NumberOfDeletes = 25;
        break;
    case 2:
        i = 50;
        NumberOfDeletes = 50;
        break;
    case 3:
        i = 70;
        NumberOfDeletes = 70;
        break;
    default:
        i = 25;
        NumberOfDeletes = 25;
        break;
    }


    int licznik = 0;
    while (licznik < NumberOfDeletes) {
        int randX = (std::rand() % 9);
        int randY = (std::rand() % 9);
        if (IsDeletable(randX, randY)) {
            Delete(randX, randY);
            licznik++;
        }
    }

    DoneBoard[8][8] = MisteriouslyChangingInt;

    return NumberOfDeletes;

}

bool back::SolveInput()
{
    bool wyn = SudokuSolver(Board);

    return wyn;
}

bool back::SudokuSolver(int Table[9][9])
{
    int row, col;
    if (!FindUnassignedLocation(row, col))
        // success!
        return true;

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {

        // Check if looks promising
        if (IsSafe(row, col, num))
        {

            // Make tentative assignment
            Table[row][col] = num;

            // Return, if success
            if (SudokuSolver(Table))
                return true;

            // Failure, unmake & try again
            Table[row][col] = 0;
        }
    }

    for (int i = 0; i < 9; i++) {
        Liczby[i] = 9;
    }
    // This triggers backtracking
    return false;
}