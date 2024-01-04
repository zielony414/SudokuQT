#include "WynikGry.h"

WynikGry::WynikGry(QObject* parent) : QObject(parent), Sec(0), Min(0), score(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WynikGry::updateTimer);
}

void WynikGry::StartTimer() {
    Sec = 0;
    timer->start(1000); // Uruchamia timer z interwałem 1 sekundy.
}

void WynikGry::StopTimer() {
    timer->stop();
    Min = 0;
    Sec = 0;
}


void WynikGry::AddPoints(int Board[9][9], int x, int y)
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

    score += points;

    emit aktualizujPunkty(score);
}

void WynikGry::AddMinus(double points)
{
    double modifier = 1.2;
    ++NrOfMistakes;
    
    int i = 0;
    
    while (i < NrOfMistakes / 3) {
        points = points * modifier;
        i++;
    }
    
    score = score - points;

    if (score < -500) {
        score = -500;
    }

    emit aktualizujPunkty(score);
}

void WynikGry::ClearData()
{
    score = 0;
    Sec = 0;
    Min = 0;
    NrOfMistakes = 0;
}

int WynikGry::GetScore()
{
    return score;
}

void WynikGry::updateTimer() {
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

