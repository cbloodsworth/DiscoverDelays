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
    // import flight data
    string fileName = "updated_2008.csv";

    fstream inputFile;
    inputFile.open(fileName, ios::in);
    string line;

    short int month, delay;
    int count = 0;
    int index = 0;
    int rows = 463128; // number of data points
    pair<short int, short int>* flights = new pair<short int, short int>[rows];  // pair<delay, month>

    while (getline(inputFile, line)) {
        if (count == rows)
            break;
        string temp;
        temp = line.substr(0, line.find(','));

        // get first number, the month
        if (temp != "NA") {
            month = stoi(temp);
        }

        // get second number, the delay time
        temp = line.substr(line.find(',') + 1, line.size() - line.find(','));
        if (temp != "NA") {
            delay = stoi(temp);
            pair<short int, short int> newPair = make_pair(delay, month);
            // add pair to flights array
            flights[index] = newPair;
            index++;
        }
        count++;
    }

    cout << "Finished reading in flight data..." << endl;

    // make a copy of flights to run 2 sorting algorithms
    pair<short int, short int>* temp = new pair<short int, short int>[index];
    for (int i = 0; i < index; i++)
        temp[i] = flights[i];

    // run each algorithm and record the runtime for both
    cout << "Performing merge sort..." << endl;
    auto start = high_resolution_clock::now();
    mergeSort(flights, 0, index);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Using merge sort took " << duration.count() << " microseconds!" << endl;

    cout << "Performing quick sort..." << endl;
    start = high_resolution_clock::now();
    quickSort(temp, 0, index);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Using quick sort took " << duration.count() << " microseconds!" << endl;

    // initialise number of delays per month to 0
    int months[13];
    for (int i = 1; i < 13; i++)
        months[i] = 0;

    // take top 25% delay times (best delay times/no delay/early arrival) and record the month for each
    for (int i = 0; i < 0.25 * index; i++) {
        months[flights[i].second]++;
    }

    // find the month with the most instances
    int best = 0;
    int bestMonth = 0;
    for (int i = 1; i < 13; i++) {
        if (months[i] > best) {
            best = months[i];
            bestMonth = i;
        }
    }
    cout << "The month with the most 'best' delays (including early arrivals!) is month number " << bestMonth << "!" << endl;

    // initialise number of delays per month to 0
    for (int i = 1; i < 13; i++)
        months[i] = 0;

    // take bottom 25% delay times (worst delay times) and record the month for each
    for (int i = index - 1; i > 0.75 * index; i--) {
        months[flights[i].second]++;
    }

    // find the month with the most instances
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
