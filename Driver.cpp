#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <array>
#include <chrono>
#include "MergeSort.h"
#include "Sorting.h"
using namespace std::chrono;
using namespace std;

// used https://www.cplusplus.com/reference/ for reference
// used https://www.geeksforgeeks.org/measure-execution-time-function-cpp/ for reference on displaying runtime
int main() {
    string fileName;
    cin >> fileName;

    fstream inputFile; 
    inputFile.open(fileName, ios::in);
    string line;

    short int month, delay;
    bool isMonth = true;
    int count = 0;
    int index = 0;
    int rows = 150000;
    pair<short int, short int> flights[rows];

    while(getline(inputFile, line)) {
        if (count == rows)
            break;
        string temp;
        temp = line.substr(0, line.find(','));
        if (temp != "NA") {
            month = stoi(temp);
        }

        temp = line.substr(line.find(',') + 1, line.size() - line.find(','));
        if (temp != "NA") {
            delay = stoi(temp);
            pair<short int, short int> newPair = make_pair(delay, month);
            flights[index] = newPair;
            index++;
        }
        count++;
    }

    cout << "Finished reading in flight data..." << endl;

    pair<short int, short int> temp[count];
    for (int i = 0; i < count; i++) 
        temp[i] = flights[i];

    cout << "Performing merge sort..." << endl;
    auto start = high_resolution_clock::now();
    mergeSort(flights, 0, rows);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Using merge sort took " << duration.count() << " microseconds!" << endl;

    cout << "Performing quick sort..." << endl;
    start = high_resolution_clock::now();
    quickSort(temp, 0, rows);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Using quick sort took " << duration.count() << " microseconds!" << endl;

    int months[13];
    for (int i = 1; i < 13; i++)
        months[i] = 0;

    for (int i = 0; i < 0.25 * rows; i++) {
        months[flights[i].second]++;
    }

    int best = 0;
    int bestMonth = 0;
    for (int i = 1; i < 13; i++) {
        if (months[i] > best) {
            best = months[i];
            bestMonth = i;
        }
    }
    cout << "The month with the most 'best' delays (including early arrivals!) is month number " << bestMonth << "!" << endl;

    for (int i = 1; i < 13; i++)
        months[i] = 0;

    for (int i = rows - 1; i > 0.75 * rows; i--) {
        months[flights[i].second]++;
    }

    int worst = 0;
    int worstMonth = 0;
    for (int i = 1; i < 13; i++) {
        if (months[i] > worst) {
            worst = months[i];
            worstMonth = i;
        }
    }
    cout << "The month with the most 'worst' delays is month number " << worstMonth << "!" << endl;
}
