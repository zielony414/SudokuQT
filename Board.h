#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


class back
{
public:
	bool IsSafe(int const row, int const col, int const num) const;
	bool IsCorrect(int const x, int const y, int const num);
	void Clear();
	void Insert(int row, int col, int num);
	int Retrive(int row, int col, int boardNr);
	bool IsDeletable(int const x, int const y);
	int(&GetTable())[9][9];
	void Play(int poziomTrud);
	bool SolveInput();
	void BlankBoard();


private:
	int Board[9][9] = { 0 };
	int DoneBoard[9][9] = { 0 };
	int Liczby[9] = { 9 };

	void Delete(int row, int col);
	bool FindUnassignedLocation(int& row, int& col);
	bool SudokuSolver(int Table[9][9]);
	void DrawNumber(int count);
};