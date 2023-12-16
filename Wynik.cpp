#include "Wynik.h"
#include <chrono>
#include <iostream>


Wynik::Wynik(QWidget* mainUi) : mainUi(mainUi) {}

int Wynik::GetScore()
{
    return score;
}

void Wynik::SetScoreZero()
{
    score = 0;
}

void Wynik::AddPoints()
{
}

void Wynik::BonusPoints()
{
}

void Wynik::StopTime()
{
    if (running) {
        running = false;
        if (timerThread.joinable()) {
            timerThread.join();
        }
    }
}

void Wynik::StartTime()
{
    if (!running) {
        running = true;
        timerThread = std::thread(&Wynik::IncrementTime, this);
    }
}

int Wynik::GetTime()
{
    return seconds;
}

void Wynik::RestartTime()
{
}

void Wynik::IncrementTime()
{
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        seconds++;

        if (mainUi) {
            // Do something with mainUi
        }
    }
}
