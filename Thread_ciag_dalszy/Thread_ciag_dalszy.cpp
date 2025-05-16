
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>

std::atomic<int> licznik{ 0 };
std::atomic<int> licznik_bufor{ 0 };
std::mutex mtx;

void inkrementuj(int ile_razy) {
    for (int i=0; i < ile_razy; i++) licznik++;
}

void zapisz_bufor(std::vector<std::string>& bufor) {
    
    int ktorybufor = licznik_bufor;
    licznik_bufor++;
    for (int i =0; i < 33; i++) {
        
        if (i % 10 == 0)std::this_thread::yield();              //yield musze jeszcze zobaczyc co i jak bo nie czaje
        mtx.lock();
        std::string zdanie = "Witam bufor nr."+ std::to_string(ktorybufor);
        //zdanie += std::to_string(i);
        bufor.push_back(zdanie);
        mtx.unlock();
    }
}

int main()
{
    
    srand(time(0));

    //ZAD 1
    int N_1 = rand() % 100;
    int N_2 = rand() % 100;
    std::thread thread_1(inkrementuj, N_1);
    std::thread thread_2(inkrementuj, N_2);
    std::cout << "N to: " << N_1 << ", " << N_2 << std::endl;
    thread_1.join();
    thread_2.join();
    std::cout << "Zinkrementowano licznik " << licznik << " razy\n";
    
    //ZAD 2
    
    std::vector<std::string> bufor;
    std::thread watek1(zapisz_bufor, std::ref(bufor));
    std::thread watek2(zapisz_bufor, std::ref(bufor));
    std::thread watek3(zapisz_bufor, std::ref(bufor));

    watek1.join();
    watek2.join();
    watek3.join();
    for (std::string var : bufor) {
        std::cout << var << std::endl;
    }
    
}
