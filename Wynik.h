#ifndef WYNIK_H
#define WYNIK_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <string>

class Wynik : public QObject {
    Q_OBJECT

public:
    explicit Wynik(QObject* parent = nullptr);
    std::string GetTime();
    void StartTimer();
    void StopTimer();
    int GetScore();
    void AddScore(int linia, bool kwadrat, bool liczba);

signals:
    void aktualizujCzasGry(std::string czas);
    void aktualizujPunkty(int points);

private slots:
    void updateTimer();

private:
    QTimer* timer;
    int Sec;
    int Min;
    int score;
    std::string czas;
};

#endif // WYNIK_H