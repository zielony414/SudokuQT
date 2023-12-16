#pragma once
#include "MainWindow.h"
#include <thread>

#include <atomic>

class Wynik
{
public:
	Wynik(QWidget* mainUi);

	int GetScore();
	void SetScoreZero();
	void AddPoints();
	void BonusPoints();
	void StopTime();
	void StartTime();
	int GetTime();
	void RestartTime();

private:
	void IncrementTime();

	std::atomic<bool> running{ false };
	std::atomic<int> seconds{ 0 };
	std::thread timerThread;
	int score = 0;
	QWidget* mainUi;
};

