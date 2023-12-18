#include "Wynik.h"
#include "MainWindow.h"


Wynik::Wynik() : isCounting(false), sekundy(0), minuty(0), score(0) {}
Wynik::~Wynik()
{
    if (isCounting) {
        stopTime();
    }
}


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

void Wynik::startTime() {
    if (!isCounting) {
        isCounting = true;
        counterThread = std::thread(&Wynik::timeCounter, this);
    }
}

void Wynik::stopTime() {
    if (isCounting) {
        isCounting = false;
        counterThread.join();
    }
}


void Wynik::timeCounter() {
    while (isCounting) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++sekundy;
        if (sekundy > 59) {
            ++minuty;
            sekundy = 0;
        }
        czas = minuty + ":" + sekundy;
        MainWindow::UpdateTime(czas);
    }
}


