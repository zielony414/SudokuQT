#include "Wynik.h"

Wynik::Wynik(QObject* parent) : QObject(parent), Sec(0), Min(0), score(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Wynik::updateTimer);
}

std::string Wynik::GetTime()
{
    return czas;
}

void Wynik::StartTimer() {
    Sec = 0;
    timer->start(1000); // Uruchamia timer z interwałem 1 sekundy.
}

void Wynik::StopTimer() {
    timer->stop();
    Min = 0;
    Sec = 0;
}

int Wynik::GetScore()
{
    return score;
}

void Wynik::AddScore(int linia, bool kwadrat, bool liczba)
{
    switch (linia) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void Wynik::updateTimer() {
    Sec++;
    if (Sec == 60) {
        Sec = 0;
        ++Min;
    }
    if ((Sec / 10) == 0) {
        czas = std::to_string(Min) + ":0" + std::to_string(Sec);
    }
    else {
        czas = std::to_string(Min) + ":" + std::to_string(Sec);
    }

    emit aktualizujCzasGry(czas);
}