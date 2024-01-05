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

    connect(&wynik_gry, SIGNAL(aktualizujCzasGry(std::string)), this, SLOT(aktualizujCzasGry(std::string)), Qt::UniqueConnection);
    connect(&wynik_gry, SIGNAL(aktualizujPunkty(int)), this, SLOT(aktualizujPunkty(int)), Qt::UniqueConnection);



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
    InitializeBoardButtons();
}

MainWindow::~MainWindow()
{
}

void MainWindow::aktualizujCzasGry(std::string czas) 
{
    ui.CzasLicznikLbl->setText(QString::fromStdString(czas));
}

void MainWindow::aktualizujPunkty(int points) 
{
    ui.PunktyLicznikLbl->setText(QString::number(points));
}


/*----------------Funkcje działające na tablicy----------------*/
void MainWindow::ClearTable()
{
    RevertColour();
    Backend.Clear();
    wynik_gry.ClearData();
    std::fill(Liczby.begin(), Liczby.end(), 0);

    ui.WiadomoscGraLbl->setText("");
    ui.PunktyLicznikLbl->setText("0");
    ui.CzasLicznikLbl->setText("0:00");

    for (int i = 0; i < 9; i++) {
        NumberButtons[i]->setEnabled(true);
        NumberButtons[i]->setStyleSheet(StylAktywnych);
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
            BoardButtons[i][j]->setText("");
        }
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
                if ((BoardButtons[i][j]->text().toInt()) == ClickedBoardNumber) {
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


        for (int i = 0; i < 10; i++) {
            if (i > 8) {
                EndGame();
                break;
            }
            else {
                if (Liczby[i] < 9) {
                    NumberButtons[i]->setChecked(true);
                    ClickedNumber = i + 1;
                    RevertColour();
                    HighlightNumbers(ClickedNumber);
                    break;
                }
            }
        }
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

    if (CreatingSudoku == false) 
    {
        if (Backend.IsCorrect(x, y, num))
        {
            BoardButtons[x][y]->setText(QString::number(ClickedNumber));
            ClickedBoardNumber = BoardButtons[x][y]->text().toInt();
            HighlightTable(x, y, ClickedBoardNumber);
            AddToCounter(ClickedBoardNumber);
            Backend.Insert(x, y, num);
            wynik_gry.AddPoints(Backend.GetTable(), x, y);
            return true;
        }
        else 
        {
            ClickedBoardNumber = BoardButtons[x][y]->text().toInt();
            HighlightTable(x, y, ClickedBoardNumber);
            if (ClickedBoardNumber == 0) wynik_gry.AddMinus(20);
            return false;
        }
    }
    else if(Backend.IsSafe(x,y,num))
    {
        BoardButtons[x][y]->setText(QString::number(ClickedNumber));
        ClickedBoardNumber = BoardButtons[x][y]->text().toInt();
        HighlightTable(x, y, ClickedBoardNumber);
        AddToCounter(ClickedBoardNumber);
        Backend.Insert(x, y, num);
        return true;
    }
    else
    {
        ClickedBoardNumber = BoardButtons[x][y]->text().toInt();
        HighlightTable(x, y, ClickedBoardNumber);
        if (ClickedBoardNumber == 0) wynik_gry.AddMinus(20);
        return false;
    }

    
}

void MainWindow::EndGame()
{
    wynik_gry.StopTimer();
    ui.WiadomoscGraLbl->setText("Gratulacje! Rozwiązałeś sudoku");
    ui.PodpowiedzButton->setEnabled(false);

    if (NazwaUzytkownika != "")
    {
        wyniki.ExportScore(NazwaUzytkownika, wynik_gry.GetScore(), Trudnosc);
    }
}


/*------------------------Główne menu------------------------*/
void MainWindow::on_GrajButton_clicked() 
{
    CreatingSudoku = false;
    ui.PodpowiedzButton->setEnabled(true);
    ui.MenuWidget->setVisible(false);
    ui.LvlWidget->setVisible(true);
};

void MainWindow::on_StworzButton_clicked()
{
    CreatingSudoku = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }

    Backend.BlankBoard();


    ui.MenuWidget->setVisible(false);
    ui.WypelnijWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
};

void MainWindow::on_UzytkownikButton_clicked()
{
    ui.WiadomoscUzytkownik->setText("Jako gość twoje wyniki nie będą zapisane!");
    ui.MenuWidget->setVisible(false);
    ui.NieZmieniajNazwyBtn->setVisible(true);
    ui.UzytkownikWidget->setVisible(true);
};

void MainWindow::on_WynikiButton_clicked()
{
    ui.WynikiText->clear();
    std::vector Scoreboard = wyniki.ImportScore();
    ui.WynikiText->setAlignment(Qt::AlignLeft);
    ui.WynikiText->append("<p>\n</p>");

    for (size_t i = 0; i < Scoreboard.size(); ++i) {
        ui.WynikiText->append("<p align='center'>" + QString::number(i+1) + "\t" + QString::fromStdString(Scoreboard[i]) + "</p>");
    }

    ui.MenuWidget->setVisible(false);
    ui.TabelaWynWidget->setVisible(true);
}


/*---------------------Menu wyboru poziomu---------------------*/
void MainWindow::on_Lvl1Button_clicked()
{
    Backend.Play(1);
    Trudnosc = "Łatwy";


    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = Backend.Retrive(i, j, 0);
        }
    }


    FillTable(board);
    


    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
    HighlightNumbers(ClickedNumber);
    wynik_gry.StartTimer();
}

void MainWindow::on_Lvl2Button_clicked()
{
    Backend.Play(2);
    Trudnosc = "Średni";
    

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = Backend.Retrive(i, j, 0);
        }
    }

    FillTable(board);
    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
    HighlightNumbers(ClickedNumber);
    wynik_gry.StartTimer();
}

void MainWindow::on_Lvl3Button_clicked()
{
    Backend.Play(3);
    Trudnosc = "Trudny";


    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = Backend.Retrive(i, j, 0);
        }
    }

    FillTable(board);
    ui.LvlWidget->setVisible(false);
    ui.GameWidget->setVisible(true);
    ui.PlanszaWidget->setVisible(true);
    HighlightNumbers(ClickedNumber);
    wynik_gry.StartTimer();
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
    wynik_gry.AddMinus(40);

    srand(time(NULL));

    int randX = (std::rand() % 9);
    int randY = (std::rand() % 9);

    while(true) {

        if (board[randX][randY] == 0) {
            int number = Backend.Retrive(randX, randY, 1);

            RevertColour();

            BoardButtons[randX][randY]->setText(QString::number(number));
            BoardButtons[randX][randY]->setStyleSheet("background-color: #a9add1;");
            AddToCounter(number);
            Backend.Insert(randX, randY, number);
            board[randX][randY] = number;
            break;
        }
        
        randX++;
        if (randX > 8) {
            randY++;
            randX = 0;
        }
        
        if (randY > 8) {
            randY = 0;
        }
    } 

}

void MainWindow::on_PorzucGreButton_clicked() 
{    
    ui.GameWidget->setVisible(false);
    ui.PlanszaWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
    ClearTable();
}



/*-------------------Panel rozwiązywania sudoku-------------------*/
void MainWindow::on_WyjdzWypelnij_clicked() 
{
    ui.WypelnijWidget->setVisible(false);
    ui.PlanszaWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
    ClearTable();
}

void MainWindow::on_RozwiazSudoku_clicked() 
{
    bool CzyRozwiazane = Backend.SolveInput();

    if (CzyRozwiazane == true) 
    {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = Backend.Retrive(i, j, 0);
            }
        }

        FillTable(board);
    }
    else 
    {
        ui.WynikWypelnieniaLbl->setText("Plansza nie jest możliwa do rozwiązania");
    }
}

void MainWindow::on_WyczyscSudoku_clicked() 
{
    ClearTable();
    FillTable(board);
}


/*-------------------------Panel wyników-------------------------*/
void MainWindow::on_WyjdzWynikiButton_clicked() {
    
    ui.TabelaWynWidget->setVisible(false);
    ui.MenuWidget->setVisible(true);
}


/*--------------------Panel przycisków planszy--------------------*/
/* Wybór numeru do wypełnienia */
void MainWindow::on_nr1Btn_clicked() { ClickedNumber = 1; RevertColour(); HighlightNumbers(1);}
void MainWindow::on_nr2Btn_clicked() { ClickedNumber = 2; RevertColour(); HighlightNumbers(2);}
void MainWindow::on_nr3Btn_clicked() { ClickedNumber = 3; RevertColour(); HighlightNumbers(3);}
void MainWindow::on_nr4Btn_clicked() { ClickedNumber = 4; RevertColour(); HighlightNumbers(4);}
void MainWindow::on_nr5Btn_clicked() { ClickedNumber = 5; RevertColour(); HighlightNumbers(5);}
void MainWindow::on_nr6Btn_clicked() { ClickedNumber = 6; RevertColour(); HighlightNumbers(6);}
void MainWindow::on_nr7Btn_clicked() { ClickedNumber = 7; RevertColour(); HighlightNumbers(7);}
void MainWindow::on_nr8Btn_clicked() { ClickedNumber = 8; RevertColour(); HighlightNumbers(8);}
void MainWindow::on_nr9Btn_clicked() { ClickedNumber = 9; RevertColour(); HighlightNumbers(9);}


/* Przyciski z planszy */
void MainWindow::on_Button11_clicked() { 
     OnButtonPress(1, 1, ClickedNumber);
}
void MainWindow::on_Button12_clicked() {
     OnButtonPress(1, 2, ClickedNumber);
}
void MainWindow::on_Button13_clicked() {
     OnButtonPress(1, 3, ClickedNumber);
}
void MainWindow::on_Button14_clicked() {
     OnButtonPress(1, 4, ClickedNumber);
}
void MainWindow::on_Button15_clicked() {
     OnButtonPress(1, 5, ClickedNumber);
}
void MainWindow::on_Button16_clicked() {
     OnButtonPress(1, 6, ClickedNumber);

}
void MainWindow::on_Button17_clicked() {
     OnButtonPress(1, 7, ClickedNumber);

}
void MainWindow::on_Button18_clicked() {
     OnButtonPress(1, 8, ClickedNumber);
}
void MainWindow::on_Button19_clicked() {
    OnButtonPress(1, 9, ClickedNumber);
}

void MainWindow::on_Button21_clicked() {
     OnButtonPress(2, 1, ClickedNumber);
}
void MainWindow::on_Button22_clicked() {
     OnButtonPress(2, 2, ClickedNumber);
}
void MainWindow::on_Button23_clicked() {
     OnButtonPress(2, 3, ClickedNumber);
}
void MainWindow::on_Button24_clicked() {
     OnButtonPress(2, 4, ClickedNumber);
}
void MainWindow::on_Button25_clicked() {
     OnButtonPress(2, 5, ClickedNumber);
}
void MainWindow::on_Button26_clicked() {
     OnButtonPress(2, 6, ClickedNumber);
}
void MainWindow::on_Button27_clicked() {
     OnButtonPress(2, 7, ClickedNumber);
}
void MainWindow::on_Button28_clicked() {
     OnButtonPress(2, 8, ClickedNumber);
}
void MainWindow::on_Button29_clicked() {
     OnButtonPress(2, 9, ClickedNumber);
}

void MainWindow::on_Button31_clicked() {
     OnButtonPress(3, 1, ClickedNumber);
}
void MainWindow::on_Button32_clicked() {
     OnButtonPress(3, 2, ClickedNumber);
}
void MainWindow::on_Button33_clicked() {
     OnButtonPress(3, 3, ClickedNumber);
}
void MainWindow::on_Button34_clicked() {
     OnButtonPress(3, 4, ClickedNumber);
}
void MainWindow::on_Button35_clicked() {
     OnButtonPress(3, 5, ClickedNumber);
}
void MainWindow::on_Button36_clicked() {
     OnButtonPress(3, 6, ClickedNumber);
}
void MainWindow::on_Button37_clicked() {
     OnButtonPress(3, 7, ClickedNumber);
}
void MainWindow::on_Button38_clicked() {
     OnButtonPress(3, 8, ClickedNumber);
}
void MainWindow::on_Button39_clicked() {
     OnButtonPress(3, 9, ClickedNumber);
}

void MainWindow::on_Button41_clicked() {
     OnButtonPress(4, 1, ClickedNumber);
}
void MainWindow::on_Button42_clicked() {
     OnButtonPress(4, 2, ClickedNumber);
}
void MainWindow::on_Button43_clicked() {
     OnButtonPress(4, 3, ClickedNumber);
}
void MainWindow::on_Button44_clicked() {
     OnButtonPress(4, 4, ClickedNumber);
}
void MainWindow::on_Button45_clicked() {
     OnButtonPress(4, 5, ClickedNumber);
}
void MainWindow::on_Button46_clicked() {
     OnButtonPress(4, 6, ClickedNumber);
}
void MainWindow::on_Button47_clicked() {
     OnButtonPress(4, 7, ClickedNumber);
}
void MainWindow::on_Button48_clicked() {
     OnButtonPress(4, 8, ClickedNumber);
}
void MainWindow::on_Button49_clicked() {
     OnButtonPress(4, 9, ClickedNumber);
}

void MainWindow::on_Button51_clicked() {
     OnButtonPress(5, 1, ClickedNumber);
}
void MainWindow::on_Button52_clicked() {
     OnButtonPress(5, 2, ClickedNumber);
}
void MainWindow::on_Button53_clicked() {
     OnButtonPress(5, 3, ClickedNumber);
}
void MainWindow::on_Button54_clicked() {
     OnButtonPress(5, 4, ClickedNumber);
}
void MainWindow::on_Button55_clicked() {
     OnButtonPress(5, 5, ClickedNumber);
}
void MainWindow::on_Button56_clicked() {
     OnButtonPress(5, 6, ClickedNumber);
}
void MainWindow::on_Button57_clicked() {
     OnButtonPress(5, 7, ClickedNumber);
}
void MainWindow::on_Button58_clicked() {
     OnButtonPress(5, 8, ClickedNumber);
}
void MainWindow::on_Button59_clicked() {
     OnButtonPress(5, 9, ClickedNumber);
}

void MainWindow::on_Button61_clicked() {
     OnButtonPress(6, 1, ClickedNumber);
}
void MainWindow::on_Button62_clicked() {
     OnButtonPress(6, 2, ClickedNumber);
}
void MainWindow::on_Button63_clicked() {
     OnButtonPress(6, 3, ClickedNumber);
}
void MainWindow::on_Button64_clicked() {
     OnButtonPress(6, 4, ClickedNumber);
}
void MainWindow::on_Button65_clicked() {
     OnButtonPress(6, 5, ClickedNumber);
}
void MainWindow::on_Button66_clicked() {
     OnButtonPress(6, 6, ClickedNumber);
}
void MainWindow::on_Button67_clicked() {
     OnButtonPress(6, 7, ClickedNumber);
}
void MainWindow::on_Button68_clicked() {
     OnButtonPress(6, 8, ClickedNumber);
}
void MainWindow::on_Button69_clicked() {
     OnButtonPress(6, 9, ClickedNumber);
}

void MainWindow::on_Button71_clicked() {
     OnButtonPress(7, 1, ClickedNumber);
}
void MainWindow::on_Button72_clicked() {
     OnButtonPress(7, 2, ClickedNumber);
}
void MainWindow::on_Button73_clicked() {
     OnButtonPress(7, 3, ClickedNumber);
}
void MainWindow::on_Button74_clicked() {
     OnButtonPress(7, 4, ClickedNumber);
}
void MainWindow::on_Button75_clicked() {
     OnButtonPress(7, 5, ClickedNumber);
}
void MainWindow::on_Button76_clicked() {
     OnButtonPress(7, 6, ClickedNumber);
}
void MainWindow::on_Button77_clicked() {
     OnButtonPress(7, 7, ClickedNumber);
}
void MainWindow::on_Button78_clicked() {
     OnButtonPress(7, 8, ClickedNumber);
}
void MainWindow::on_Button79_clicked() {
     OnButtonPress(7, 9, ClickedNumber);
}

void MainWindow::on_Button81_clicked() {
     OnButtonPress(8, 1, ClickedNumber);
}
void MainWindow::on_Button82_clicked() {
     OnButtonPress(8, 2, ClickedNumber);
}
void MainWindow::on_Button83_clicked() {
     OnButtonPress(8, 3, ClickedNumber);
}
void MainWindow::on_Button84_clicked() {
     OnButtonPress(8, 4, ClickedNumber);
}
void MainWindow::on_Button85_clicked() {
     OnButtonPress(8, 5, ClickedNumber);
}
void MainWindow::on_Button86_clicked() {
     OnButtonPress(8, 6, ClickedNumber);
}
void MainWindow::on_Button87_clicked() {
     OnButtonPress(8, 7, ClickedNumber);
}
void MainWindow::on_Button88_clicked() {
     OnButtonPress(8, 8, ClickedNumber);
}
void MainWindow::on_Button89_clicked() {
     OnButtonPress(8, 9, ClickedNumber);
}

void MainWindow::on_Button91_clicked() {
     OnButtonPress(9, 1, ClickedNumber);
}
void MainWindow::on_Button92_clicked() {
     OnButtonPress(9, 2, ClickedNumber);
}
void MainWindow::on_Button93_clicked() {
     OnButtonPress(9, 3, ClickedNumber);
}
void MainWindow::on_Button94_clicked() {
     OnButtonPress(9, 4, ClickedNumber);
}
void MainWindow::on_Button95_clicked() {
     OnButtonPress(9, 5, ClickedNumber);
}
void MainWindow::on_Button96_clicked() {
     OnButtonPress(9, 6, ClickedNumber);
}
void MainWindow::on_Button97_clicked() {
     OnButtonPress(9, 7, ClickedNumber);
}
void MainWindow::on_Button98_clicked() {
    OnButtonPress(9, 8, ClickedNumber);
}
void MainWindow::on_Button99_clicked() {
    OnButtonPress(9, 9, ClickedNumber);
}