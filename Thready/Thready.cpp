// Thready.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <future>


void Generacja_10(std::vector<int>& podany) {
    for (int i = 0; i < 100; ++i) {
        podany[i] = rand() % 11;
    }
}
void Generacja_100(std::vector<int>& podany) {
    for (int i = 0; i < 100; ++i) {
        podany[i] = rand() % 101;
    }
}
void Wypisz(std::vector<int> podany) {
    for (int i = 0; i < 100; ++i) {
        std::cout << podany[i] << " ";
    }
    std::cout << std::endl;
}

void Zlicz(std::vector<int> podany, int co_liczy, int p_np,int& wystapienia) {
    int ile = 0;
    for (int i = p_np*(podany.size()/2); i < (podany.size() / (2 - p_np)); ++i) {
        if (podany[i] == co_liczy)++ile;
    }
    std::cout << "W "<< p_np+1<<" polowie wystepuje " << ile << " razy\n";
    wystapienia += ile;
}

int main()
{
    std::vector<int> wektor(100);
    int pobrana_liczba=0;
    int suma_wystapien=0;
    Generacja_10(wektor);
    
    std::cout << "Jaka liczbe chcialbys zliczyc w wektorze?\n";
    //std::cin.ignore();
    std::cin >> pobrana_liczba;
    
    //ZAD1

    std::thread t1(Zlicz, std::ref(wektor), std::ref(pobrana_liczba), 0, std::ref(suma_wystapien));     //ref apparently jest potrzebny zeby sie nie sypalo
    std::thread t2(Zlicz, std::ref(wektor), std::ref(pobrana_liczba), 1, std::ref(suma_wystapien));
    
    t1.join();
    t2.join();
    std::cout << "Wystapienia: " << suma_wystapien << std::endl;
    Wypisz(wektor);


    //ZAD2
}

