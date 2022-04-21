#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <array>
using namespace std;

// used https://www.cplusplus.com/reference/ for reference
// pair<delay, month>
void merge(pair<short int, short int> flights[], int start, int middle, int end) {
    pair<short int, short int> left[middle - start + 1];
    pair<short int, short int> right[end - middle];

    // initialise left and right copies
    for (int i = 0; i < middle - start + 1; i++) {
        left[i] = flights[start + i];
    }
    for (int i = 0; i < end - middle; i++) {
        right[i] = flights[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = start;

    // while elements left in either copy
    while(i < middle - start + 1 && j < end - middle) {
        // compare and put smaller element in flights[k]
        if (left[i].first <= right[j].first) {
            flights[k] = left[i];
            i = i + 1;
        }
        else {
            flights[k] = right[j];
            j = j + 1;
        }
        k = k + 1;
    }

    // append elements if needed
    while (i < middle - start + 1) {
        flights[k] = left[i];
        i = i + 1;
        k = k + 1;
    }
    while (j < end - middle) {
        flights[k] = right[j];
        j = j + 1;
        k = k + 1;
    }
}

void mergeSort(pair<short int, short int> flights[], int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        // sort left
        mergeSort(flights, start, middle);
        // sort right
        mergeSort(flights, middle + 1, end);
        // merge sorted left and right
        merge(flights, start, middle, end);
    }
}
