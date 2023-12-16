#include "MainWindow.h"
/*----------------------Inicjalizacja----------------------*/
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    StylNieaktywnych =
        "QRadioButton{display: inline-block;"
        "background-color: #b1b1b1;"
        "font-size: 18px;"
        "border: 2px solid #444;"
        "border-radius: 4px;"
        "padding: 8px 20px;}"
        "QRadioButton::indicator{"
        "opacity : 0;"
        "position: fixed;"
        "width : 0;}";

    StylAktywnych =
        "QRadioButton{display: inline-block;"
        "background-color: #ddd;"
        "padding:10px 20px;"
        "font-size:18px;"
        "border: 2px solid #444;"
        "border-radius:4px;}"
        "QRadioButton:hover{"
        "background-color:#dfd;}"
        "QRadioButton::indicator{"
        "opacity:0;"
        "position: fixed;"
        "width:0;}"
        "QRadioButton::pressed{"
        "border:2px dashed #444;}"
        "QRadioButton::checked{"
        "background-color: #bfb;"
        "border-color: #4c4;}";

    Liczby.resize(9, 0);
    WynikGry = 0;

    ui.setupUi(this);
    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(false);
    ui.MenuWidget->setVisible(false);
    ui.PlanszaWidget->setVisible(false);
    ui.TabelaWynWidget->setVisible(false);
    ui.UzytkownikLabel->setVisible(false);
    ui.WypelnijWidget->setVisible(false);
    ui.plainTextEdit->setVisible(false);
    ui.NieZmieniajNazwyBtn->setVisible(false);
    InitializeNumberButtons();
}

MainWindow::~MainWindow()
{
    delete &ui;
}

//Ui::MainWindowClass* MainWindow::getUi() const
//{
//    return ui;
//}


/*----------------Funkcje działające na tablicy----------------*/
void MainWindow::ClearTable()
{
    Backend.Clear();
    std::fill(Liczby.begin(), Liczby.end(), 0);
    WynikGry = 0;

    for (int i = 0; i < 9; i++) {
        NumberButtons[i]->setEnabled(true);
        NumberButtons[i]->setStyleSheet(StylAktywnych);
    }
}

void MainWindow::FillTable(int Board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (BoardButtons[i][j]) {
                if (Board[i][j] == 0) 
                {
                    BoardButtons[i][j]->setText("");
                }
                else
                {
                    BoardButtons[i][j]->setText(QString::number(Board[i][j]));
                    AddToCounter(Board[i][j]);
                }
            }
            else {
                qDebug() << "Button not found: ";
            }
        }
    }

}

void MainWindow::HighlightTable(int x, int y, int num) {

    if ((BoardButtons[x][y]->text().toInt())==0){
        BoardButtons[x][y]->setStyleSheet("background-color: #d16f6f;");
    }
    else
    {   
        // Zmiana kolorów przycisków obszaru 3x3
        int startRow = (x - (x % 3));
        int startCol = (y - (y % 3));

        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (BoardButtons[i][j]) {
                    BoardButtons[i][j]->setStyleSheet("background-color: #ced0eb;");
                }
                else {
                    qDebug() << "Button not found: ";
                }
            }
        }
        
        // Zmiana koloru wszystkich liczb takich jak wciśnięty przycisk
        for (int i = 0; i < 9; i++) {
            // zmiana kolorów przycisków w rzędzie
            BoardButtons[x][i]->setStyleSheet("background-color: #ced0eb;");
            // zmiania kolorów przycisków w kolumnie
            BoardButtons[i][y]->setStyleSheet("background-color: #ced0eb;");
            for (int j = 0; j < 9; j++) {
                if ((BoardButtons[i][j]->text().toInt()) == ClickedNumber) {
                    BoardButtons[i][j]->setStyleSheet("background-color: #a9add1;");
                }
            }
        }
        // Zmiana koloru wciśniętego przycisku
        BoardButtons[x][y]->setStyleSheet("background-color: #a9add1;");
    }
}

void MainWindow::HighlightNumbers(int num)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((BoardButtons[i][j]->text().toInt()) == num) {
                BoardButtons[i][j]->setStyleSheet("background-color: #a9add1;");
            }
        }
    }
}

void MainWindow::RevertColour() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            BoardButtons[i][j]->setStyleSheet("background-color: #edeef7;");
        }
    }
}


/*-------------Funkcje działające na przyciskach-------------*/
void MainWindow::AddToCounter(int number) {

    Liczby[number-1]++;
    if (Liczby[number-1] >= 9) {
        NumberButtons[number - 1]->setEnabled(false);
        NumberButtons[number - 1]->setStyleSheet(StylNieaktywnych);
    }
}

void MainWindow::InitializeBoardButtons()
{
    // Przechowuje wskaźniki do przycisków znalezionych w pierwszej pętli
    for (int i = 1; i < 10; i++) {
        QVector<QPushButton*> rowButtons;  // Przyciski w danym rzędzie
        for (int j = 1; j < 10; j++) {
            QString buttonName = "Button" + QString::number(i) + QString::number(j);
            QPushButton* button = findChild<QPushButton*>(buttonName);

            // Dodaj przycisk do wektora reprezentującego rzęd
            rowButtons.push_back(button);
        }
        // Dodaj wektor reprezentujący rzęd do wektora reprezentującego całą tablicę
        BoardButtons.push_back(rowButtons);
    }
}

void MainWindow::InitializeNumberButtons()
{
    for (int i = 1; i < 10; i++) {
        QString buttonName = "nr" + QString::number(i) + "Btn";
        QRadioButton* button = findChild<QRadioButton*>(buttonName);

        // Dodaj przycisk do wektora 
        NumberButtons.push_back(button);
    }
}

bool MainWindow::OnButtonPress(int x, int y, int num)
{
    // Konwersja na przedział 0 - 8
    --x;
    --y;

    RevertColour();


    if (Backend.IsSafe(x, y, num))
    {
        BoardButtons[x][y]->setText(QString::number(NrPrzycisku));
        ClickedNumber = BoardButtons[x][y]->text().toInt();
        HighlightTable(x, y, ClickedNumber);
        AddToCounter(ClickedNumber);
        Backend.Insert(x, y, num);
        ui.WiadomoscGraLbl->setText("");
        return true;
    }
    else {
        ClickedNumber = BoardButtons[x][y]->text().toInt();
        HighlightTable(x, y, ClickedNumber);
        ui.WiadomoscGraLbl->setText("");
        return false;
    }
}


/*------------------------Główne menu------------------------*/
void MainWindow::on_GrajButton_clicked() 
{
    ui.MenuWidget->setVisible(false);
    ui.LvlWidget->setVisible(true);
};

void MainWindow::on_StworzButton_clicked()
{
    ui.MenuWidget->setVisible(false);
    ui.WypelnijWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
};

void MainWindow::on_UzytkownikButton_clicked()
{
    ui.MenuWidget->setVisible(false);
    ui.NieZmieniajNazwyBtn->setVisible(true);
    ui.UzytkownikWidget->setVisible(true);
};

void MainWindow::on_WynikiButton_clicked()
{
    ui.MenuWidget->setVisible(false);
    ui.TabelaWynWidget->setVisible(true);
}


/*---------------------Menu wyboru poziomu---------------------*/
void MainWindow::on_Lvl1Button_clicked()
{
    InitializeBoardButtons();

    ClearTable();
    Backend.Play(1);


    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = Backend.Retrive(i, j);
        }
    }

    FillTable(board);

    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
}

void MainWindow::on_Lvl2Button_clicked()
{
    InitializeBoardButtons();

    ClearTable();
    Backend.Play(2);
    

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = Backend.Retrive(i, j);
        }
    }

    FillTable(board);

    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
}

void MainWindow::on_Lvl3Button_clicked()
{
    InitializeBoardButtons();

    ClearTable();
    Backend.Play(3);


    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = Backend.Retrive(i, j);
        }
    }

    FillTable(board);

    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
}


/*----------------------Panel zmiany nazwy----------------------*/
void MainWindow::on_UstawNazweBtn_clicked() {

    QString QNazwaUzytkownika = ui.WpiszNazweLine->text();
    NazwaUzytkownika = QNazwaUzytkownika.toStdString();
    
    if (NazwaUzytkownika.empty()) {
        ui.WiadomoscUzytkownik->setText("Nazwa nie została wprowadzona!");
    }
    else if (NazwaUzytkownika == "Gość") {
        ui.WiadomoscUzytkownik->setText("Nie możesz nazwać użytkownika \"Gość\"!");
    }
    else {
        ui.WiadomoscUzytkownik->setText("Jako gość twoje wyniki nie będą zapisane!");
        ui.UzytkownikLabel->setText(QString::fromStdString("Uzytkownik: ") + QNazwaUzytkownika);

        ui.UzytkownikWidget->setVisible(false);
        ui.MenuWidget->setVisible(true);
        ui.UzytkownikLabel->setVisible(true);
    }
};

void MainWindow::on_JakoGoscBtn_clicked() {
    ui.WiadomoscUzytkownik->setText("Jako gość twoje wyniki nie będą zapisane!");
    ui.UzytkownikLabel->setText("Uzytkownik: Gość");

    ui.UzytkownikWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
    ui.UzytkownikLabel->setVisible(true);
}

void MainWindow::on_NieZmieniajNazwyBtn_clicked() {
    ui.UzytkownikWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
    ui.UzytkownikLabel->setVisible(true);
};


/*-----------------------Panel gry w sudoku-----------------------*/
void MainWindow::on_PodpowiedzButton_clicked() {

}

void MainWindow::on_PorzucGreButton_clicked() {
    WynikGry = 0;
    RevertColour();
    ui.WiadomoscGraLbl->setText("");
    ui.GameWidget->setVisible(false);
    ui.PlanszaWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
}


/*-------------------Panel rozwiązywania sudoku-------------------*/
void MainWindow::on_WyjdzWypelnij_clicked() {
    ui.WypelnijWidget->setVisible(false);
    ui.PlanszaWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
}

void MainWindow::on_RozwiazSudoku_clicked() {

}

void MainWindow::on_WyczyscSudoku_clicked() {

}


/*-------------------------Panel wyników-------------------------*/
void MainWindow::on_WyjdzWynikiButton_clicked() {
    ui.TabelaWynWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
}


/*--------------------Panel przycisków planszy--------------------*/
/* Wybór numeru do wypełnienia */
void MainWindow::on_nr1Btn_clicked() { NrPrzycisku = 1; RevertColour(); HighlightNumbers(1);}
void MainWindow::on_nr2Btn_clicked() { NrPrzycisku = 2; RevertColour(); HighlightNumbers(2);}
void MainWindow::on_nr3Btn_clicked() { NrPrzycisku = 3; RevertColour(); HighlightNumbers(3);}
void MainWindow::on_nr4Btn_clicked() { NrPrzycisku = 4; RevertColour(); HighlightNumbers(4);}
void MainWindow::on_nr5Btn_clicked() { NrPrzycisku = 5; RevertColour(); HighlightNumbers(5);}
void MainWindow::on_nr6Btn_clicked() { NrPrzycisku = 6; RevertColour(); HighlightNumbers(6);}
void MainWindow::on_nr7Btn_clicked() { NrPrzycisku = 7; RevertColour(); HighlightNumbers(7);}
void MainWindow::on_nr8Btn_clicked() { NrPrzycisku = 8; RevertColour(); HighlightNumbers(8);}
void MainWindow::on_nr9Btn_clicked() { NrPrzycisku = 9; RevertColour(); HighlightNumbers(9);}



/* Przyciski z planszy */
void MainWindow::on_Button11_clicked() { 
     OnButtonPress(1, 1, NrPrzycisku);
}
void MainWindow::on_Button12_clicked() {
     OnButtonPress(1, 2, NrPrzycisku);
}
void MainWindow::on_Button13_clicked() {
     OnButtonPress(1, 3, NrPrzycisku);
}
void MainWindow::on_Button14_clicked() {
     OnButtonPress(1, 4, NrPrzycisku);
}
void MainWindow::on_Button15_clicked() {
     OnButtonPress(1, 5, NrPrzycisku);
}
void MainWindow::on_Button16_clicked() {
     OnButtonPress(1, 6, NrPrzycisku);

}
void MainWindow::on_Button17_clicked() {
     OnButtonPress(1, 7, NrPrzycisku);

}
void MainWindow::on_Button18_clicked() {
     OnButtonPress(1, 8, NrPrzycisku);
}
void MainWindow::on_Button19_clicked() {
    OnButtonPress(1, 9, NrPrzycisku);
}

void MainWindow::on_Button21_clicked() {
     OnButtonPress(2, 1, NrPrzycisku);
}
void MainWindow::on_Button22_clicked() {
     OnButtonPress(2, 2, NrPrzycisku);
}
void MainWindow::on_Button23_clicked() {
     OnButtonPress(2, 3, NrPrzycisku);
}
void MainWindow::on_Button24_clicked() {
     OnButtonPress(2, 4, NrPrzycisku);
}
void MainWindow::on_Button25_clicked() {
     OnButtonPress(2, 5, NrPrzycisku);
}
void MainWindow::on_Button26_clicked() {
     OnButtonPress(2, 6, NrPrzycisku);
}
void MainWindow::on_Button27_clicked() {
     OnButtonPress(2, 7, NrPrzycisku);
}
void MainWindow::on_Button28_clicked() {
     OnButtonPress(2, 8, NrPrzycisku);
}
void MainWindow::on_Button29_clicked() {
     OnButtonPress(2, 9, NrPrzycisku);
}

void MainWindow::on_Button31_clicked() {
     OnButtonPress(3, 1, NrPrzycisku);
}
void MainWindow::on_Button32_clicked() {
     OnButtonPress(3, 2, NrPrzycisku);
}
void MainWindow::on_Button33_clicked() {
     OnButtonPress(3, 3, NrPrzycisku);
}
void MainWindow::on_Button34_clicked() {
     OnButtonPress(3, 4, NrPrzycisku);
}
void MainWindow::on_Button35_clicked() {
     OnButtonPress(3, 5, NrPrzycisku);
}
void MainWindow::on_Button36_clicked() {
     OnButtonPress(3, 6, NrPrzycisku);
}
void MainWindow::on_Button37_clicked() {
     OnButtonPress(3, 7, NrPrzycisku);
}
void MainWindow::on_Button38_clicked() {
     OnButtonPress(3, 8, NrPrzycisku);
}
void MainWindow::on_Button39_clicked() {
     OnButtonPress(3, 9, NrPrzycisku);
}

void MainWindow::on_Button41_clicked() {
     OnButtonPress(4, 1, NrPrzycisku);
}
void MainWindow::on_Button42_clicked() {
     OnButtonPress(4, 2, NrPrzycisku);
}
void MainWindow::on_Button43_clicked() {
     OnButtonPress(4, 3, NrPrzycisku);
}
void MainWindow::on_Button44_clicked() {
     OnButtonPress(4, 4, NrPrzycisku);
}
void MainWindow::on_Button45_clicked() {
     OnButtonPress(4, 5, NrPrzycisku);
}
void MainWindow::on_Button46_clicked() {
     OnButtonPress(4, 6, NrPrzycisku);
}
void MainWindow::on_Button47_clicked() {
     OnButtonPress(4, 7, NrPrzycisku);
}
void MainWindow::on_Button48_clicked() {
     OnButtonPress(4, 8, NrPrzycisku);
}
void MainWindow::on_Button49_clicked() {
     OnButtonPress(4, 9, NrPrzycisku);
}

void MainWindow::on_Button51_clicked() {
     OnButtonPress(5, 1, NrPrzycisku);
}
void MainWindow::on_Button52_clicked() {
     OnButtonPress(5, 2, NrPrzycisku);
}
void MainWindow::on_Button53_clicked() {
     OnButtonPress(5, 3, NrPrzycisku);
}
void MainWindow::on_Button54_clicked() {
     OnButtonPress(5, 4, NrPrzycisku);
}
void MainWindow::on_Button55_clicked() {
     OnButtonPress(5, 5, NrPrzycisku);
}
void MainWindow::on_Button56_clicked() {
     OnButtonPress(5, 6, NrPrzycisku);
}
void MainWindow::on_Button57_clicked() {
     OnButtonPress(5, 7, NrPrzycisku);
}
void MainWindow::on_Button58_clicked() {
     OnButtonPress(5, 8, NrPrzycisku);
}
void MainWindow::on_Button59_clicked() {
     OnButtonPress(5, 9, NrPrzycisku);
}

void MainWindow::on_Button61_clicked() {
     OnButtonPress(6, 1, NrPrzycisku);
}
void MainWindow::on_Button62_clicked() {
     OnButtonPress(6, 2, NrPrzycisku);
}
void MainWindow::on_Button63_clicked() {
     OnButtonPress(6, 3, NrPrzycisku);
}
void MainWindow::on_Button64_clicked() {
     OnButtonPress(6, 4, NrPrzycisku);
}
void MainWindow::on_Button65_clicked() {
     OnButtonPress(6, 5, NrPrzycisku);
}
void MainWindow::on_Button66_clicked() {
     OnButtonPress(6, 6, NrPrzycisku);
}
void MainWindow::on_Button67_clicked() {
     OnButtonPress(6, 7, NrPrzycisku);
}
void MainWindow::on_Button68_clicked() {
     OnButtonPress(6, 8, NrPrzycisku);
}
void MainWindow::on_Button69_clicked() {
     OnButtonPress(6, 9, NrPrzycisku);
}

void MainWindow::on_Button71_clicked() {
     OnButtonPress(7, 1, NrPrzycisku);
}
void MainWindow::on_Button72_clicked() {
     OnButtonPress(7, 2, NrPrzycisku);
}
void MainWindow::on_Button73_clicked() {
     OnButtonPress(7, 3, NrPrzycisku);
}
void MainWindow::on_Button74_clicked() {
     OnButtonPress(7, 4, NrPrzycisku);
}
void MainWindow::on_Button75_clicked() {
     OnButtonPress(7, 5, NrPrzycisku);
}
void MainWindow::on_Button76_clicked() {
     OnButtonPress(7, 6, NrPrzycisku);
}
void MainWindow::on_Button77_clicked() {
     OnButtonPress(7, 7, NrPrzycisku);
}
void MainWindow::on_Button78_clicked() {
     OnButtonPress(7, 8, NrPrzycisku);
}
void MainWindow::on_Button79_clicked() {
     OnButtonPress(7, 9, NrPrzycisku);
}

void MainWindow::on_Button81_clicked() {
     OnButtonPress(8, 1, NrPrzycisku);
}
void MainWindow::on_Button82_clicked() {
     OnButtonPress(8, 2, NrPrzycisku);
}
void MainWindow::on_Button83_clicked() {
     OnButtonPress(8, 3, NrPrzycisku);
}
void MainWindow::on_Button84_clicked() {
     OnButtonPress(8, 4, NrPrzycisku);
}
void MainWindow::on_Button85_clicked() {
     OnButtonPress(8, 5, NrPrzycisku);
}
void MainWindow::on_Button86_clicked() {
     OnButtonPress(8, 6, NrPrzycisku);
}
void MainWindow::on_Button87_clicked() {
     OnButtonPress(8, 7, NrPrzycisku);
}
void MainWindow::on_Button88_clicked() {
     OnButtonPress(8, 8, NrPrzycisku);
}
void MainWindow::on_Button89_clicked() {
     OnButtonPress(8, 9, NrPrzycisku);
}

void MainWindow::on_Button91_clicked() {
     OnButtonPress(9, 1, NrPrzycisku);
}
void MainWindow::on_Button92_clicked() {
     OnButtonPress(9, 2, NrPrzycisku);
}
void MainWindow::on_Button93_clicked() {
     OnButtonPress(9, 3, NrPrzycisku);
}
void MainWindow::on_Button94_clicked() {
     OnButtonPress(9, 4, NrPrzycisku);
}
void MainWindow::on_Button95_clicked() {
     OnButtonPress(9, 5, NrPrzycisku);
}
void MainWindow::on_Button96_clicked() {
     OnButtonPress(9, 6, NrPrzycisku);
}
void MainWindow::on_Button97_clicked() {
     OnButtonPress(9, 7, NrPrzycisku);
}
void MainWindow::on_Button98_clicked() {
    OnButtonPress(9, 8, NrPrzycisku);
}
void MainWindow::on_Button99_clicked() {
    OnButtonPress(9, 9, NrPrzycisku);
}