#pragma once

#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

class Wyniki
{
public:
    bool ExportScore(const std::string& NazwaUzytkownika, int Wynik, const std::string& Trudnosc);
    const std::vector < std::string > ImportScore();

private:
    struct PlayerScore {
        std::string nazwaUzytkownika;
        std::string wynik;
        std::string poziomTrudnosci;
        std::string czas;
    };

    void convertToStr();
    std::vector<PlayerScore> Scoreboard;
    std::vector<std::string> ScoreboardConverted;
    const std::string nazwaPliku = "WynikiSudoku.txt";
    PlayerScore parsujWiersz(const std::string& wiersz);
    void wczytajDaneZPliku(const std::string& nazwaPliku);
};


