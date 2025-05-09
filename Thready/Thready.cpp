// Thready.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <future>
#include <cmath>


void Generacja_10(std::vector<int>& podany) {
    for (int i = 0; i < 100; ++i) {
        podany[i] = rand() % 11;
    }
}

void Generacja_100(std::vector<int>& podany) {
    for (int i = 0; i < 100; ++i) {
        podany[i] = (rand() % 201)-100;       //generowanie liczb z zakresu 200 i "przesuniecie" ich
        
    }
}

void Wypisz(std::vector<int> podany) {
    std::cout << std::endl;
    for (int i = 0; i < 100; ++i) {
        std::cout << podany[i] << " ";
    }
    std::cout << std::endl;
}

void Zlicz(std::vector<int> podany, int co_liczy, int p_np,int& wystapienia) {      //p_np aka parzyste nie parzyste samo przypisze wątkom ich czesc zakresu
    int ile = 0;
    for (int i = p_np*(podany.size()/2); i < (podany.size() / (2 - p_np)); ++i) {
        if (podany[i] == co_liczy)++ile;
    }
    std::cout << "W "<< p_np+1<<" polowie wystepuje " << ile << " razy\n";
    wystapienia += ile;
}

int Sortuj(std::vector<int> wektor, int& petla) {
    int petla2 = petla;
    petla += 1;
    int najmniejsza = 100;
    for (int i = (petla2 * 25); i < (petla * 25); i++) {
        if (wektor[i] < najmniejsza)najmniejsza = wektor[i];
    }
    return najmniejsza;
}

void Dodatnie(int l1,int l2,int l3) {           //istnieje jedynie do rzucania errorow gdy podamy nieodpowiednia liczbe
    if (l1 < 0 || l2 < 0 || l3 < 0)
    throw std::invalid_argument("Podaj dodatnie i calkowite");
}

void Dzielniki(int liczebka,std::promise<int> pro) {
    int wynik = 1;
    for (int i = 1; i <= (liczebka/2); i++) {
        if (liczebka % i == 0)
            wynik++;
    }
    pro.set_value(wynik);
}


int main()
{
    std::vector<int> wektor(100);
    std::vector<int> wektor2(100);
    int pobrana_liczba=0;
    int suma_wystapien=0;
    int numer_wywolania_sortowania = 0;
    Generacja_10(wektor);
    
    std::cout << "Jaka liczbe chcialbys zliczyc w wektorze?\n";
    
    std::cin >> pobrana_liczba;
    
    //ZAD1

    std::thread t1z1(Zlicz, std::ref(wektor), std::ref(pobrana_liczba), 0, std::ref(suma_wystapien));     //ref apparently jest potrzebny zeby sie nie sypalo
    std::thread t2z1(Zlicz, std::ref(wektor), std::ref(pobrana_liczba), 1, std::ref(suma_wystapien));
    
    t1z1.join();
    t2z1.join();
    std::cout << "Wystapienia: " << suma_wystapien << std::endl;
    Wypisz(wektor);


    //ZAD2
    Generacja_100(wektor2);
    Wypisz(wektor2);
    std::future<int> F0 = std::async(std::launch::async, Sortuj, std::ref(wektor2), std::ref(numer_wywolania_sortowania));
    std::future<int> F1 = std::async(std::launch::async, Sortuj, std::ref(wektor2), std::ref(numer_wywolania_sortowania));
    std::future<int> F2 = std::async(std::launch::async, Sortuj, std::ref(wektor2), std::ref(numer_wywolania_sortowania));
    std::future<int> F3 = std::async(std::launch::async, Sortuj, std::ref(wektor2), std::ref(numer_wywolania_sortowania));
    //std::cout << "\nNajmniejsze liczby w czterech czesciach tego wektora to: " << F0.get() << ", " << F1.get() << ", " << F2.get() << ", " << F3.get() << std::endl;
    std::vector<int>najmniejszy_wynik{ F0.get(),F1.get(),F2.get(),F3.get() };
    std::sort(najmniejszy_wynik.begin(), najmniejszy_wynik.end());
    std::cout << "\nNajmniejsza liczba wygenerowana w tej petli to: " << najmniejszy_wynik[0] << std::endl;
    

    //ZAD3
   

    int liczba1, liczba2, liczba3;
    std::cout << "\nPodaj 3 liczby dodatnie\n";
    std::cin >> liczba1 >> liczba2 >> liczba3;
    
    try { Dodatnie(liczba1, liczba2, liczba3); }         //sprawdzanie czy sa dodatnie i rzucanie errora jak nie
    catch (std::invalid_argument& e) { std::cerr << e.what() << std::endl; return-1; }

    std::promise<int>prom1, prom2, prom3, prom4;
    std::future<int> fut1 = prom1.get_future();
    std::future<int> fut2 = prom2.get_future();
    std::future<int> fut3 = prom3.get_future();

    std::thread t1z3(Dzielniki, std::ref(liczba1), std::move(prom1));//thread 1 zadanie 3
    std::thread t2z3(Dzielniki, std::ref(liczba2), std::move(prom2));
    std::thread t3z3(Dzielniki, std::ref(liczba3), std::move(prom3));

    t1z3.join();
    t2z3.join();
    t3z3.join();

    std::cout << "\nLiczby dzielnikow w podanych liczbach wynosza: \nLiczba 1: " << fut1.get() << "\nLiczba 2: " << fut2.get() << "\nLiczba 3: " << fut3.get() << std::endl;

    
}

