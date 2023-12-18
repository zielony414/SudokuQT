#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Back.h"
#include "Wynik.h"
#include <vector>
#include <iostream>
#include <string>
#include <QVector>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    static void UpdateTime(string time);
    static void UpdateScore(int score);

    back Backend;
    Wynik wyn;

private:
    Ui::MainWindowClass ui;

    QLabel* LabelCzas;
    std::string NazwaUzytkownika;
    int NrPrzycisku = 1;
    int WynikGry;
    vector <int> Liczby;
    int ClickedNumber = 0;
    QVector<QVector<QPushButton*>> BoardButtons;
    QVector<QRadioButton*> NumberButtons;
    int board[9][9] = {0};
    const char* StylNieaktywnych;
    const char* StylAktywnych;

    void ClearTable();
    void AddToCounter(int number);
    void InitializeBoardButtons();
    void InitializeNumberButtons();
    void RevertColour();
    void HighlightTable(int x, int y, int num);
    void HighlightNumbers(int num);
    bool OnButtonPress(int x, int y, int num );
    void FillTable(int Board[9][9]);


private slots:
    void on_GrajButton_clicked();
    void on_StworzButton_clicked();
    void on_UzytkownikButton_clicked();
    void on_WynikiButton_clicked();

    void on_Lvl1Button_clicked();
    void on_Lvl2Button_clicked();
    void on_Lvl3Button_clicked();

    void on_PodpowiedzButton_clicked();
    void on_PorzucGreButton_clicked();

    
    void on_nr1Btn_clicked();
    void on_nr2Btn_clicked();
    void on_nr3Btn_clicked();
    void on_nr4Btn_clicked();
    void on_nr5Btn_clicked();
    void on_nr6Btn_clicked();
    void on_nr7Btn_clicked();
    void on_nr8Btn_clicked();
    void on_nr9Btn_clicked();

    void on_JakoGoscBtn_clicked();
    void on_NieZmieniajNazwyBtn_clicked();
    void on_UstawNazweBtn_clicked();

    void on_RozwiazSudoku_clicked(); 
    void on_WyjdzWypelnij_clicked();
    void on_WyczyscSudoku_clicked();

    void on_WyjdzWynikiButton_clicked();

    void on_Button11_clicked();
    void on_Button12_clicked();
    void on_Button13_clicked();
    void on_Button14_clicked();
    void on_Button15_clicked();
    void on_Button16_clicked();
    void on_Button17_clicked();
    void on_Button18_clicked();
    void on_Button19_clicked();

    void on_Button21_clicked();
    void on_Button22_clicked();
    void on_Button23_clicked();
    void on_Button24_clicked();
    void on_Button25_clicked();
    void on_Button26_clicked();
    void on_Button27_clicked();
    void on_Button28_clicked();
    void on_Button29_clicked();

    void on_Button31_clicked();
    void on_Button32_clicked();
    void on_Button33_clicked();
    void on_Button34_clicked();
    void on_Button35_clicked();
    void on_Button36_clicked();
    void on_Button37_clicked();
    void on_Button38_clicked();
    void on_Button39_clicked();

    void on_Button41_clicked();
    void on_Button42_clicked();
    void on_Button43_clicked();
    void on_Button44_clicked();
    void on_Button45_clicked();
    void on_Button46_clicked();
    void on_Button47_clicked();
    void on_Button48_clicked();
    void on_Button49_clicked();

    void on_Button51_clicked();
    void on_Button52_clicked();
    void on_Button53_clicked();
    void on_Button54_clicked();
    void on_Button55_clicked();
    void on_Button56_clicked();
    void on_Button57_clicked();
    void on_Button58_clicked();
    void on_Button59_clicked();

    void on_Button61_clicked();
    void on_Button62_clicked();
    void on_Button63_clicked();
    void on_Button64_clicked();
    void on_Button65_clicked();
    void on_Button66_clicked();
    void on_Button67_clicked();
    void on_Button68_clicked();
    void on_Button69_clicked();

    void on_Button71_clicked();
    void on_Button72_clicked();
    void on_Button73_clicked();
    void on_Button74_clicked();
    void on_Button75_clicked();
    void on_Button76_clicked();
    void on_Button77_clicked();
    void on_Button78_clicked();
    void on_Button79_clicked();

    void on_Button81_clicked();
    void on_Button82_clicked();
    void on_Button83_clicked();
    void on_Button84_clicked();
    void on_Button85_clicked();
    void on_Button86_clicked();
    void on_Button87_clicked();
    void on_Button88_clicked();
    void on_Button89_clicked();

    void on_Button91_clicked();
    void on_Button92_clicked();
    void on_Button93_clicked();
    void on_Button94_clicked();
    void on_Button95_clicked();
    void on_Button96_clicked();
    void on_Button97_clicked();
    void on_Button98_clicked();
    void on_Button99_clicked();
   
};