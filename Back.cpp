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
    switch(numer){
    case 1:
        if (Liczba1 > 1) {
            Liczba1--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 2:
        if (Liczba2 > 1) {
            Liczba2--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 3:
        if (Liczba3 > 1) {
            Liczba3--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 4:
        if (Liczba4 > 1) {
            Liczba4--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 5:
        if (Liczba5 > 1) {
            Liczba5--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 6:
        if (Liczba6 > 1) {
            Liczba6--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 7:
        if (Liczba7 > 1) {
            Liczba7--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 8:
        if (Liczba8 > 1) {
            Liczba8--;
            return true;
        }
        else {
            return false;
        }
        break;
    case 9:
        if (Liczba9 > 1) {
            Liczba9--;
            return true;
        }
        else {
            return false;
        }
        break;
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
    SudokuSolver();

    switch (poziomTrud) {
    case 1:
        i = 20;
        NumberOfDeletes = 20;
        break;
    case 2:
        i = 40;
        NumberOfDeletes = 40;
        break;
    case 3:
        i = 60;
        NumberOfDeletes = 60;
        break;
    default:
        i = 20;
        NumberOfDeletes = 20;
        break;
    }

    int randX = (std::rand() % 9);
    int randY = (std::rand() % 9);

    int licznik = 0;
    while (licznik < NumberOfDeletes) {
        if (IsDeletable(randX, randY)) {
            Delete(randX, randY);
            licznik++;
        }
    }
    /*for (i; i > 0; --i) {
        int randX = (std::rand() % 9);
        int randY = (std::rand() % 9);
        
        int licznik = 0;
        while (licznik < NumberOfDeletes) {
            if (IsDeletable(randX, randY)) {
                Delete(randX, randY);
            }
        }

        if (IsDeletable(randX, randY)) {
            Delete(randX, randY);
        }
        else {
            i++;
        }
    }*/
    return NumberOfDeletes;
}

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

    Liczba1 = 9;
    Liczba2 = 9;
    Liczba3 = 9;
    Liczba4 = 9;
    Liczba5 = 9;
    Liczba6 = 9;
    Liczba7 = 9;
    Liczba8 = 9;
    Liczba9 = 9;

    // This triggers backtracking
    return false;
}