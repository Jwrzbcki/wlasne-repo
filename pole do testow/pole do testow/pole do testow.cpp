// pole do testow.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "naglowki.h"
#include <chrono>


//std::vector<std::string>znak;
//std::ofstream tlumaczenie("tlumaczenie.txt");




int main()
{
    
    std::stringstream ss;
    std::string str;
    std::string kod;
    std::ifstream zakodowany("zakodowany.txt");
    auto start = std::chrono::steady_clock::now();
    
        while (std::getline(zakodowany,str)) {
            kod += str;
            kod.push_back(' ');
        }

        ss << kod;
        std::string slowo;
        int i = 0;
        while (ss >> slowo) {
            if (slowo[0] == '.' || slowo[0] == '-') {
                
                morse_do_ascii(slowo);//, i, sizeof(slowo));
            }
            else {
                for (int i = 0; i < slowo.length(); i++) {              //sprobuj dodac spacje przy tlumaczeniu -.- na abc
                   
                    ascii_do_morse(slowo[i]);
                }
                //tlumaczenie << "/ ";
            }
        }  

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> czas_wykonywania = end - start;
        std::cout << "Czas wykonywania programu: " << czas_wykonywania.count() << std::endl;


        

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
