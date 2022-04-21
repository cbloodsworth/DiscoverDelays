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
// vector<map<delay, month>>
void merge(pair<short int, short int> flights[], int start, int middle, int end) {
    pair<short int, short int>* left = new pair<short int, short int>[middle - start + 1];
    pair<short int, short int>* right = new pair<short int, short int>[end - middle];

    for (int i = 0; i < middle - start + 1; i++) {
        left[i] = flights[start + i];
    }
    for (int i = 0; i < end - middle; i++) {
        right[i] = flights[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = start;

    while (i < middle - start + 1 && j < end - middle) {
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

    delete[] left;
    delete[] right;
}

void mergeSort(pair<short int, short int> flights[], int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        mergeSort(flights, start, middle);
        mergeSort(flights, middle + 1, end);
        merge(flights, start, middle, end);
    }
}