#pragma once
#include <QObject>
#include <QTimer>
#include <QString>
#include <string>

class GameScore : public QObject {
    Q_OBJECT

public:
    explicit GameScore(QObject* parent = nullptr);
    void StartTimer();
    void StopTimer();
    void AddPoints(int Board[9][9], int x, int y);
    void AddMinus(double points);
    void ClearData();
    int GetScore();
    

private:
    QTimer* Timer;
    int Sec;
    int Min;
    int NrOfMistakes = 0;
    double Score;
    std::string Czas;

signals:
    void aktualizujCzasGry(std::string czas);
    void aktualizujPunkty(int points);

private slots:
    void updateTimer();


};
