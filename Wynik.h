#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <string>


class MainWindow;

class Wynik
{
public:
	Wynik();
	~Wynik();

	int GetScore();
	void SetScoreZero();
	void AddPoints();
	void BonusPoints();
	void startTime();
	void stopTime();

private:
	std::thread counterThread;
	bool isCounting;
	int sekundy;
	int minuty;
	int score;
	std::string czas;

	void timeCounter();
};

