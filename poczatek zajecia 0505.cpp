// ConsoleApplication11.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>



class walidator {
public:
    int x;
};

class telefon_kom : walidator {
public:
    std::string numer;
    
    //metoda valid <- lancuch    -> true false
};

class kwota : walidator {

    //std::cin 
private :
    int min;
    int max;
};

class email : walidator {

};

class telefon_stac : walidator {

};


int main()
{
    telefon_kom telefon;
    
    bool poprawnosc;
    
    do {
       poprawnosc = false;
       std::cout << "prosze podac numer telefonu" << std::endl;
       std::cin >> telefon.numer;

       if (telefon.numer.length() != 9) { 
           poprawnosc = true; 
           std::cout << "Niepoprawny numer telefonu" << std::endl; 
           break; 
       };

       for (int i = (telefon.numer.length()-1); i > 0; i--) {
           if ((telefon.numer[i] < 48) || (telefon.numer[i] > 57)) {
               poprawnosc = true;
               std::cout << "Niepoprawny numer telefonu" << std::endl;
               break;
           }
       }
    } while (poprawnosc == 1);
}
