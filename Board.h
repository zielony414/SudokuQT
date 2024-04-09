#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


class Board
{
public:
	bool IsSafe(int row, int col, int num);
	bool IsCorrect(int x, int y, int num);
	void Clear();
	void Insert(int row, int col, int num);
	int Retrive(int row, int col, int boardNr);
	bool IsDeletable(int x, int y);
	int(&GetTable())[9][9];
	void Play(int poziomTrud);
	bool SolveInput();

	int PlayBoard[9][9] = { 0 };
	int DoneBoard[9][9] = { 0 };

private:
	int Liczby[9] = { 9 };

	bool FindUnassignedLocation(int& row, int& col);
	bool SudokuSolver(int Table[9][9]);
	void DrawNumber(int count);
	
};