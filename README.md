# Sudoku QT - Klasyczna Gra Logiczna w C++

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/Framework-Qt_5/6-green?style=for-the-badge&logo=qt" />
</p>

## O Projekcie

**Sudoku QT** to w pełni funkcjonalna aplikacja desktopowa pozwalająca na grę w Sudoku, zbudowana z wykorzystaniem języka **C++** i biblioteki **Qt**. Projekt skupia się na implementacji efektywnych algorytmów generowania planszy oraz zapewnieniu intuicyjnego interfejsu użytkownika.

Aplikacja demonstruje zastosowanie wzorca obiektowego oraz logiki algorytmicznej (backtracking) do weryfikacji poprawności i rozwiązywania łamigłówek.

## Kluczowe Funkcjonalności

- **Interaktywna Plansza:** Czytelny interfejs graficzny pozwalający na wprowadzanie cyfr i nawigację.
- **Logika Gry:** System sprawdzania poprawności wprowadzonych danych zgodnie z zasadami Sudoku.
- **Dynamiczne GUI:** Wykorzystanie sygnałów i slotów (Signals & Slots) frameworka Qt do obsługi zdarzeń użytkownika.
- **Wsparcie dla zasobów:** Implementacja niestandardowej szaty graficznej (tła, ikony) za pomocą plików `.qrc`.

## Technologie i Narzędzia

- **Język:** C++ (Standard 17+)
- **Framework:** Qt (Widgets Module)
- **Narzędzia:** - **Qt Designer** – do projektowania układu interfejsu (`MainWindow.ui`).
  - **Visual Studio** – jako główne środowisko programistyczne (wykorzystanie MSVC).
  - **qmake** – system budowania projektu.

## Struktura Projektu

- `main.cpp` – Punkt wejścia aplikacji, inicjalizacja głównego okna.
- `MainWindow.cpp/h` – Logika głównego okna aplikacji i obsługa interfejsu.
- `Plansza.cpp/h` – Klasa odpowiedzialna za reprezentację danych planszy i zasady gry.
- `Back.cpp/h` – Moduł odpowiedzialny za logikę "pod maską" (backend aplikacji).
- `MainWindow.ui` – Definicja wizualna interfejsu (XML).
