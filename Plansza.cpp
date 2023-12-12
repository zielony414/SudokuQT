#include "Plansza.h"



bool Plansza::OnButtonPress(int x, int y, int num)
{
    // Konwersja na przedział 0 - 8
    --x;
    --y;

    RevertColour();


    if (Backend.IsSafe(x, y, num))
    {
        BoardButtons[x][y]->setText(QString::number(NrPrzycisku));
        ClickedNumber = BoardButtons[x][y]->text().toInt();
        HighlightNumbers(x, y, ClickedNumber);
        AddToCounter(ClickedNumber);
        Backend.Insert(x, y, num);
        ui.WiadomoscGraLbl->setText("");
        return true;
    }
    else {
        ClickedNumber = BoardButtons[x][y]->text().toInt();
        HighlightNumbers(x, y, ClickedNumber);
        ui.WiadomoscGraLbl->setText("");
        return false;
    }
}

void Plansza::InitializeBoardButtons()
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

void Plansza::FillTable(int Board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (BoardButtons[i][j]) {
                if (Board[i][j] != 0) {
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

void Plansza::HighlightNumbers(int x, int y, int num) {
    // zmiana kolorów przycisków w rzędzie
    for (int i = 0; i < 9; ++i) {
        if (BoardButtons[x][i]) {
            BoardButtons[x][i]->setStyleSheet("background-color: #ced0eb;");
        }
        else {
            qDebug() << "Button not found: ";
        }

        // zmiania kolorów przycisków w kolumnie
        if (BoardButtons[i][y]) {
            BoardButtons[i][y]->setStyleSheet("background-color: #ced0eb;");
        }
        else {
            qDebug() << "Button not found: ";
        }
    }

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
        for (int j = 0; j < 9; j++) {
            if ((BoardButtons[i][j]->text().toInt()) == ClickedNumber) {
                BoardButtons[i][j]->setStyleSheet("background-color: #a9add1;");
            }
            else {
                qDebug() << "Button not found: ";
            }
        }
    }
}

void Plansza::RevertColour() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            BoardButtons[i][j]->setStyleSheet("background-color: #edeef7;");
        }
    }
}


/* Przyciski z planszy */
void Plansza::on_Button11_clicked() {
    OnButtonPress(1, 1, NrPrzycisku);
}
void Plansza::on_Button12_clicked() {
    OnButtonPress(1, 2, NrPrzycisku);
}
void Plansza::on_Button13_clicked() {
    OnButtonPress(1, 3, NrPrzycisku);
}
void Plansza::on_Button14_clicked() {
    OnButtonPress(1, 4, NrPrzycisku);
}
void Plansza::on_Button15_clicked() {
    OnButtonPress(1, 5, NrPrzycisku);
}
void Plansza::on_Button16_clicked() {
    OnButtonPress(1, 6, NrPrzycisku);

}
void Plansza::on_Button17_clicked() {
    OnButtonPress(1, 7, NrPrzycisku);

}
void Plansza::on_Button18_clicked() {
    OnButtonPress(1, 8, NrPrzycisku);
}
void Plansza::on_Button19_clicked() {
    OnButtonPress(1, 9, NrPrzycisku);
}

void Plansza::on_Button21_clicked() {
    OnButtonPress(2, 1, NrPrzycisku);
}
void Plansza::on_Button22_clicked() {
    OnButtonPress(2, 2, NrPrzycisku);
}
void Plansza::on_Button23_clicked() {
    OnButtonPress(2, 3, NrPrzycisku);
}
void Plansza::on_Button24_clicked() {
    OnButtonPress(2, 4, NrPrzycisku);
}
void Plansza::on_Button25_clicked() {
    OnButtonPress(2, 5, NrPrzycisku);
}
void Plansza::on_Button26_clicked() {
    OnButtonPress(2, 6, NrPrzycisku);
}
void Plansza::on_Button27_clicked() {
    OnButtonPress(2, 7, NrPrzycisku);
}
void Plansza::on_Button28_clicked() {
    OnButtonPress(2, 8, NrPrzycisku);
}
void Plansza::on_Button29_clicked() {
    OnButtonPress(2, 9, NrPrzycisku);
}

void Plansza::on_Button31_clicked() {
    OnButtonPress(3, 1, NrPrzycisku);
}
void Plansza::on_Button32_clicked() {
    OnButtonPress(3, 2, NrPrzycisku);
}
void Plansza::on_Button33_clicked() {
    OnButtonPress(3, 3, NrPrzycisku);
}
void Plansza::on_Button34_clicked() {
    OnButtonPress(3, 4, NrPrzycisku);
}
void Plansza::on_Button35_clicked() {
    OnButtonPress(3, 5, NrPrzycisku);
}
void Plansza::on_Button36_clicked() {
    OnButtonPress(3, 6, NrPrzycisku);
}
void Plansza::on_Button37_clicked() {
    OnButtonPress(3, 7, NrPrzycisku);
}
void Plansza::on_Button38_clicked() {
    OnButtonPress(3, 8, NrPrzycisku);
}
void Plansza::on_Button39_clicked() {
    OnButtonPress(3, 9, NrPrzycisku);
}

void Plansza::on_Button41_clicked() {
    OnButtonPress(4, 1, NrPrzycisku);
}
void Plansza::on_Button42_clicked() {
    OnButtonPress(4, 2, NrPrzycisku);
}
void Plansza::on_Button43_clicked() {
    OnButtonPress(4, 3, NrPrzycisku);
}
void Plansza::on_Button44_clicked() {
    OnButtonPress(4, 4, NrPrzycisku);
}
void Plansza::on_Button45_clicked() {
    OnButtonPress(4, 5, NrPrzycisku);
}
void Plansza::on_Button46_clicked() {
    OnButtonPress(4, 6, NrPrzycisku);
}
void Plansza::on_Button47_clicked() {
    OnButtonPress(4, 7, NrPrzycisku);
}
void Plansza::on_Button48_clicked() {
    OnButtonPress(4, 8, NrPrzycisku);
}
void Plansza::on_Button49_clicked() {
    OnButtonPress(4, 9, NrPrzycisku);
}

void Plansza::on_Button51_clicked() {
    OnButtonPress(5, 1, NrPrzycisku);
}
void Plansza::on_Button52_clicked() {
    OnButtonPress(5, 2, NrPrzycisku);
}
void Plansza::on_Button53_clicked() {
    OnButtonPress(5, 3, NrPrzycisku);
}
void Plansza::on_Button54_clicked() {
    OnButtonPress(5, 4, NrPrzycisku);
}
void Plansza::on_Button55_clicked() {
    OnButtonPress(5, 5, NrPrzycisku);
}
void Plansza::on_Button56_clicked() {
    OnButtonPress(5, 6, NrPrzycisku);
}
void Plansza::on_Button57_clicked() {
    OnButtonPress(5, 7, NrPrzycisku);
}
void Plansza::on_Button58_clicked() {
    OnButtonPress(5, 8, NrPrzycisku);
}
void Plansza::on_Button59_clicked() {
    OnButtonPress(5, 9, NrPrzycisku);
}

void Plansza::on_Button61_clicked() {
    OnButtonPress(6, 1, NrPrzycisku);
}
void Plansza::on_Button62_clicked() {
    OnButtonPress(6, 2, NrPrzycisku);
}
void Plansza::on_Button63_clicked() {
    OnButtonPress(6, 3, NrPrzycisku);
}
void Plansza::on_Button64_clicked() {
    OnButtonPress(6, 4, NrPrzycisku);
}
void Plansza::on_Button65_clicked() {
    OnButtonPress(6, 5, NrPrzycisku);
}
void Plansza::on_Button66_clicked() {
    OnButtonPress(6, 6, NrPrzycisku);
}
void Plansza::on_Button67_clicked() {
    OnButtonPress(6, 7, NrPrzycisku);
}
void Plansza::on_Button68_clicked() {
    OnButtonPress(6, 8, NrPrzycisku);
}
void Plansza::on_Button69_clicked() {
    OnButtonPress(6, 9, NrPrzycisku);
}

void Plansza::on_Button71_clicked() {
    OnButtonPress(7, 1, NrPrzycisku);
}
void Plansza::on_Button72_clicked() {
    OnButtonPress(7, 2, NrPrzycisku);
}
void Plansza::on_Button73_clicked() {
    OnButtonPress(7, 3, NrPrzycisku);
}
void Plansza::on_Button74_clicked() {
    OnButtonPress(7, 4, NrPrzycisku);
}
void Plansza::on_Button75_clicked() {
    OnButtonPress(7, 5, NrPrzycisku);
}
void Plansza::on_Button76_clicked() {
    OnButtonPress(7, 6, NrPrzycisku);
}
void Plansza::on_Button77_clicked() {
    OnButtonPress(7, 7, NrPrzycisku);
}
void Plansza::on_Button78_clicked() {
    OnButtonPress(7, 8, NrPrzycisku);
}
void Plansza::on_Button79_clicked() {
    OnButtonPress(7, 9, NrPrzycisku);
}

void Plansza::on_Button81_clicked() {
    OnButtonPress(8, 1, NrPrzycisku);
}
void Plansza::on_Button82_clicked() {
    OnButtonPress(8, 2, NrPrzycisku);
}
void Plansza::on_Button83_clicked() {
    OnButtonPress(8, 3, NrPrzycisku);
}
void Plansza::on_Button84_clicked() {
    OnButtonPress(8, 4, NrPrzycisku);
}
void Plansza::on_Button85_clicked() {
    OnButtonPress(8, 5, NrPrzycisku);
}
void Plansza::on_Button86_clicked() {
    OnButtonPress(8, 6, NrPrzycisku);
}
void Plansza::on_Button87_clicked() {
    OnButtonPress(8, 7, NrPrzycisku);
}
void Plansza::on_Button88_clicked() {
    OnButtonPress(8, 8, NrPrzycisku);
}
void Plansza::on_Button89_clicked() {
    OnButtonPress(8, 9, NrPrzycisku);
}

void Plansza::on_Button91_clicked() {
    OnButtonPress(9, 1, NrPrzycisku);
}
void Plansza::on_Button92_clicked() {
    OnButtonPress(9, 2, NrPrzycisku);
}
void Plansza::on_Button93_clicked() {
    OnButtonPress(9, 3, NrPrzycisku);
}
void Plansza::on_Button94_clicked() {
    OnButtonPress(9, 4, NrPrzycisku);
}
void Plansza::on_Button95_clicked() {
    OnButtonPress(9, 5, NrPrzycisku);
}
void Plansza::on_Button96_clicked() {
    OnButtonPress(9, 6, NrPrzycisku);
}
void Plansza::on_Button97_clicked() {
    OnButtonPress(9, 7, NrPrzycisku);
}
void Plansza::on_Button98_clicked() {
    OnButtonPress(9, 8, NrPrzycisku);
}
void Plansza::on_Button99_clicked() {
    OnButtonPress(9, 9, NrPrzycisku);
}