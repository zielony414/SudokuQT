#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


class back
{
public:
	void DrawNumber(int count);
	bool SudokuSolver(int Table[9][9]);
	bool IsSafe(int x, int y, int num);
	bool IsCorrect(int x, int y, int num);
	bool FindUnassignedLocation(int& row, int& col);
	void Clear();
	void Insert(int row, int col, int num);
	void Delete(int row, int col);
	int Retrive(int row, int col, int boardNr);
	bool IsDeletable(int x, int y);
	int(&GetTable())[9][9];
	int Play(int poziomTrud);
	bool SolveInput();
	
	

private:
	int Board[9][9] = { 0 };
	int DoneBoard[9][9] = { 0 };
	int Liczby[9] = { 9 };
};

