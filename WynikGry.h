#pragma once
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
    void AddMinus(double points);
    void ClearData();
    int GetScore() const;
    

private:
    QTimer* timer;
    int Sec;
    int Min;
    int NrOfMistakes = 0;
    double score;
    std::string czas;

signals:
    void aktualizujCzasGry(std::string czas);
    void aktualizujPunkty(int points);

private slots:
    void updateTimer();


};
