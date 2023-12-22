#ifndef WYNIK_H
#define WYNIK_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <string>
#include <ctime>
#include <fstream>

class Wynik : public QObject {
    Q_OBJECT

public:
    explicit Wynik(QObject* parent = nullptr);
    std::string GetTime();
    void StartTimer();
    void StopTimer();
    int GetScore();
    void CalculateBonuses(int Board[9][9], int x, int y);
    void AddMinus();
    void ClearData();
    bool ExportScore(std::string NazwaUzytkownika, std::string Trudnosc);

signals:
    void aktualizujCzasGry(std::string czas);
    void aktualizujPunkty(int points);

private slots:
    void updateTimer();

private:
    QTimer* timer;
    int Sec;
    int Min;
    int NrOfMistakes = 0;
    double score;
    std::string czas;
};

#endif // WYNIK_H