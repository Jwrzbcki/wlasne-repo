

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>
#include <queue>
#include <chrono>


std::atomic<int> licznik{ 0 };
std::mutex mtx;

void inkrementuj(int ile_razy) {
    for (int i=0; i < ile_razy; i++) licznik++;
}

std::atomic<int> licznik_bufor{ 0 };

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

std::mutex mtx_z3;
std::condition_variable cv;
std::queue<int> bufor;
const int MAX_ROZMIAR = 5;
bool koniec = false;

void producent() {
    
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx_z3);
        cv.wait(lock, [] { return bufor.size() < MAX_ROZMIAR; });
        
        bufor.push(i);
        std::cout << "[Producent]: " << i;

        lock.unlock();
        cv.notify_one(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::lock_guard<std::mutex> lock(mtx_z3);
    koniec = true;
    cv.notify_one();
}

void konsument() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_z3);
        cv.wait(lock, [] { return !bufor.empty() || koniec; });

        if (!bufor.empty()) {
            int wartosc = bufor.front();
            bufor.pop();
            std::cout << "\t\t\t\t[Konsument]: " << wartosc << "\n";

            lock.unlock();
            cv.notify_one(); 
        }
        else if (koniec) {
            break;
        }
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    
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
    std::cout << "\nLaczna liczba wartosci w buforze: " << bufor.size() << std::endl;
    
    //ZAD 3
    
    std::thread prodT(producent);
    std::thread konsT(konsument);

    prodT.join();
    konsT.join();

    std::cout << "Gotowe.\n";

    auto stop = std::chrono::high_resolution_clock::now();
    auto dlugosc_wykonania = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "\nProgram zajal: " << dlugosc_wykonania << std::endl;
}
