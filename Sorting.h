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

int partition(pair<short int, short int> arr[], int lo, int hi) {
    int up = lo - 1;
    int pivot = arr[lo].first;

    for (int down = lo; down <= hi - 1; down++) {
        if (arr[down].first < pivot) 
            swap(arr[++up], arr[hi]);
        
    }
    
    swap(arr[up + 1], arr[hi]);
    return up + 1;
}

void quickSort(pair<short int, short int> arr[], int lo, int hi) {
    if (lo < hi) {
        int pivot = partition(arr, lo, hi);
        quickSort(arr, lo, pivot - 1);
        quickSort(arr, pivot + 1, hi);
    }
}