#pragma once
using namespace std;


class back
{
public:
	void DrawNumber(int count);
	int Show();
	bool SudokuSolver();
	bool IsSafe(int x, int y, int num);
	bool FindUnassignedLocation(int& row, int& col);
	void Clear();
	void Insert(int row, int col, int num);
	int Retrive(int row, int col);
	int(&GetTable())[9][9];

private:
	int Board[9][9] = { 0 };
};

