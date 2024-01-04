﻿#include "Wyniki.h"

bool Wyniki::ExportScore(std::string NazwaUzytkownika, int Wynik, std::string Trudnosc)
{
    std::time_t czas = std::time(nullptr);
    std::tm* dataCzas = std::localtime(&czas);

    // Wyświetlenie daty w formacie "DD.MM.RRRR"
    int dzien = dataCzas->tm_mday;
    int miesiac = dataCzas->tm_mon + 1; // tm_mon liczy miesiące od 0 do 11
    int rok = dataCzas->tm_year + 1900;

    std::string Czas = std::to_string(dzien) + "." + std::to_string(miesiac) + "." + std::to_string(rok);

    std::string Export = NazwaUzytkownika + ";" + std::to_string(Wynik) + ";" + Trudnosc + ";" + Czas;

    // Otwarcie pliku w trybie do zapisu (dodawania do istniejącego pliku lub tworzenia nowego)
    std::ofstream plik(nazwaPliku, std::ios::app);

    if (plik.is_open())
    {
        plik << Export << std::endl;
        plik.close();
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> Wyniki::ImportScore()
{
    wczytajDaneZPliku(nazwaPliku);
    return ScoreboardConverted;
}

void Wyniki::wczytajDaneZPliku(const std::string& nazwaPliku) {
    
    if (Scoreboard.size() != 0) {
        Scoreboard = {};
        ScoreboardConverted = {};
    }

    std::ifstream plik(nazwaPliku);

    if (plik.is_open()) {
        std::string wiersz;
        while (std::getline(plik, wiersz)) {
            PlayerScore PlayerData = parsujWiersz(wiersz);
            Scoreboard.push_back(PlayerData);
        }
        plik.close();
    }

    convertToStr();

    std::sort(ScoreboardConverted.begin(), ScoreboardConverted.end(), [](const std::string& a, const std::string& b) {
        // Porównywanie malejąco po wartości wynik (string to liczba)
        int wynikA = std::stoi(a.substr(a.find('\t') + 1));
        int wynikB = std::stoi(b.substr(b.find('\t') + 1));
        return wynikA > wynikB;
        });

}

Wyniki::PlayerScore Wyniki::parsujWiersz(const std::string& wiersz) {
    PlayerScore PlayerData;
    std::istringstream linia(wiersz);

    std::getline(linia, PlayerData.nazwaUzytkownika, ';');
    std::getline(linia, PlayerData.wynik, ';');
    std::getline(linia, PlayerData.poziomTrudnosci, ';');
    std::getline(linia, PlayerData.czas);

    return PlayerData;
}

void Wyniki::convertToStr()
{
    for (const PlayerScore& rekord : Scoreboard) {
        std::ostringstream ss;
        ss << rekord.nazwaUzytkownika << "\t" << rekord.wynik << "\t" << rekord.poziomTrudnosci << "\t" << rekord.czas;
        ScoreboardConverted.push_back(ss.str());
    }
}
