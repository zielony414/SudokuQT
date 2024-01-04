#ifndef WYNIK_H
#define WYNIK_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <string>

class WynikGry : public QObject {
    Q_OBJECT

public:
    explicit WynikGry(QObject* parent = nullptr);
    void StartTimer();
    void StopTimer();
    void AddPoints(int Board[9][9], int x, int y);
    void AddMinus(double points = 20);
    void ClearData();
    int GetScore();
    

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