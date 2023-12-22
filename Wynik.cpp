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


void Wynik::CalculateBonuses(int Board[9][9], int x, int y)
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

void Wynik::AddMinus()
{
    double points = 10;
    double modifier = 1.2;
    ++NrOfMistakes;
    
    int i = 0;
    
    while (i < NrOfMistakes / 3) {
        points = points * modifier;
        i++;
    }
    
    
    score = score - points;

    emit aktualizujPunkty(score);
}

void Wynik::ClearData()
{
    score = 0;
    Sec = 0;
    Min = 0;
    NrOfMistakes = 0;
}

bool Wynik::ExportScore(std::string NazwaUzytkownika, std::string Trudnosc)
{
    std::time_t czas = std::time(nullptr);
    std::tm* dataCzas = std::localtime(&czas);

    // Wyświetlenie daty w formacie "DD.MM.RRRR"
    int dzien = dataCzas->tm_mday;
    int miesiac = dataCzas->tm_mon + 1; // tm_mon liczy miesiące od 0 do 11
    int rok = dataCzas->tm_year + 1900;

    std::string Czas = std::to_string(dzien) + "." + std::to_string(miesiac) + "." + std::to_string(rok);

    std::string Export = NazwaUzytkownika + ";" + std::to_string(score) + ";" + Trudnosc + ";" + Czas;

    const std::string nazwaPliku = "WynikiSudoku.txt";

    // Otwarcie pliku w trybie do zapisu (dodawania do istniejącego pliku lub tworzenia nowego)
    std::ofstream plik(nazwaPliku, std::ios::app);

    if (plik.is_open()) 
    {
        plik << Export << std::endl;
        plik.close();
        return true;
    }
    else 
    {
        return false;
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