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


int back::Show()
{
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << Board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
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

    }
    for (int i = 0; i < 9; ++i) {
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

int back::Retrive(int row, int col)
{
    return Board[row][col];
}

int(&back::GetTable())[9][9]{
    return Board;
}


// funkcja rozwiazujaca sudoku
/*pobiera macierz po czym stara sie przypisac wartosci
komorkom majacym wartosc 0 zgodnie z zasadami gry*/
bool back::SudokuSolver()
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
            Board[row][col] = num;

            // Return, if success
            if (SudokuSolver())
                return true;

            // Failure, unmake & try again
            Board[row][col] = 0;
        }
    }

    // This triggers backtracking
    return false;
}