#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <math.h>

using namespace std;

int previous;

int main(int argc, const char * argv[]) {
    void primes(long long unsigned, int, int);
    
    long long unsigned n;
    ifstream fin("previous.txt");
    int threads, threadNumber(0);
    
    if (fin) {
        fin >> previous;
        fin.close();
    }
    else {
        ofstream create("previous.txt");
        create << 0;
        previous = 0;
        create.close();
    }
    
    cout << "Enter the number of threads you would like to use: ";
    std::cin >> threads;
    
    cout << "Enter the max value to check up to: ";
    std::cin >> n;
    
    cout << "2 3 ";
    
    for (int i(0); i < threads; i++) {
        thread prime(primes, n, threads, threadNumber);
        ++threadNumber;
        prime.detach();
    }
    
    ofstream update("previous.txt");
    update << previous;
    update.close();
    
    std::cin.get();
    std::cin.get();
    
    return 0;
}

void primes(long long unsigned n, int threads, int threadNumber) {
    string fname = "primes" + to_string(previous) + ".txt";
    previous++;
    ofstream fout(fname);
    
    bool prime;
    threads = threads * 2;
    long long unsigned startValue = 5 + (2 * threadNumber);
    for (long long unsigned i(startValue); i <= n; i+=threads) {
        long double sqroot = sqrt(i);
        prime = false;
        
        for (long long unsigned j(2); j <= sqroot; j++) {
            if (i % j == 0) {
                prime = false;
                break;
            }
            else {
                prime = true;
            }
        }
        if (prime) {
            cout << i << " ";   // for "convenience"
            fout << i << "\n";
        }
    }
    fout.close();
}
