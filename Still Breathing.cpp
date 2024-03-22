// Still Breathing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <thread>
#include <ctime>
using namespace std;

const int num_threads = 4;

const size_t array_size = 1000000000;

void calculateSum(int* arr, size_t start, size_t end, long long& partial_sum) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 100);

    for (size_t i = start; i < end; i++) {
        arr[i] = dis(gen);
        partial_sum += arr[i];
    }
}

int main() {
    int* numbers = new int[array_size];

    thread threads[num_threads];
    long long total_sum = 0;

    size_t chunk_size = array_size / num_threads;
    for (int i = 0; i < num_threads; i++) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? array_size : (i + 1) * chunk_size;
        threads[i] = thread(calculateSum, numbers, start, end, ref(total_sum));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    cout << "Total sum: " << total_sum << endl;

    delete[] numbers;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
