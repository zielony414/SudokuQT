#include "GameScore.h"

GameScore::GameScore(QObject* parent) : QObject(parent), Sec(0), Min(0), Score(0) {
	Timer = new QTimer(this);
	connect(Timer, &QTimer::timeout, this, &GameScore::updateTimer);
}

void GameScore::StartTimer() {
	Sec = 0;
	Min = 0;
	Timer->start(1000); // Uruchamia timer z interwałem 1 sekundy.
}

void GameScore::StopTimer() {
	Timer->stop();
}

void GameScore::AddPoints(int Board[9][9], int x, int y)
{
	double points = 10;
	int row = 0;
	int col = 0;
	int square = 0;

	for (int i = 0; i < 9; i++) {
		if (Board[x][i] > 0) {
			++col;
		}
		if (Board[i][y] > 0) {
			++row;
		}
	}

	int startRow = (x - (x % 3));
	int startCol = (y - (y % 3));

	for (int j = startRow; j < startRow + 3; j++) {
		for (int k = startCol; k < startCol + 3; k++) {
			if (Board[j][k] > 0) {
				++square;
			}
		}
	}

	if (row == 9) {
		points += 10;
	}
	if (col == 9) {
		points += 10;
	}
	if (square == 9) {
		points += 10;
	}
	if (Min < 3) {
		points = points * 1.20;
	}
	else if (Min > 7) {
		points = points * 0.80;
	}

	Score += points;

	emit aktualizujPunkty(Score);
}

void GameScore::AddMinus(double points)
{
	++NrOfMistakes;

	if (NrOfMistakes > 4) {
		points = points * 1.6;
	}
	else if (NrOfMistakes > 2) {
		points = points * 1.2;
	}

	Score = Score - points;

	if (Score < -500) {
		Score = -500;
	}

	emit aktualizujPunkty(Score);
}

void GameScore::ClearData()
{
	Score = 0;
	Sec = 0;
	Min = 0;
	NrOfMistakes = 0;
}

int GameScore::GetScore()
{
	return Score;
}

void GameScore::updateTimer() {
	Sec++;
	if (Sec == 60) {
		Sec = 0;
		++Min;
	}
	if ((Sec / 10) == 0) {
		Czas = std::to_string(Min) + ":0" + std::to_string(Sec);
	}
	else {
		Czas = std::to_string(Min) + ":" + std::to_string(Sec);
	}

	emit aktualizujCzasGry(Czas);
}