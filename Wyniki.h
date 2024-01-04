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
    struct PlayerScore {
        std::string nazwaUzytkownika;
        std::string wynik;
        std::string poziomTrudnosci;
        std::string czas;
    };
    
    bool ExportScore(std::string NazwaUzytkownika, int Wynik, std::string Trudnosc);
    std::vector < std::string > ImportScore();

private:
    void convertToStr();
    std::vector<PlayerScore> Scoreboard;
    std::vector<std::string> ScoreboardConverted;
    const std::string nazwaPliku = "WynikiSudoku.txt";
    PlayerScore parsujWiersz(const std::string& wiersz);
    void wczytajDaneZPliku(const std::string& nazwaPliku);
};


