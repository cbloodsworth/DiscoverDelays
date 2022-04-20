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
    int up = lo;
    int down = hi;
    int pivot = arr[lo].first;

    while (up < down) {
        for (int i = up; i < hi; i++) {
            if (arr[up].first > pivot)
                break;
            up = up + 1;
        }
        for (int j = hi; j > lo; j--) {
            if (arr[down].first <= pivot)
                break;
            down = down - 1;
        }
        if (up < down)
            swap(arr[up], arr[down]);
    }
    swap(arr[lo], arr[down]);
    return down;
}

void quickSort(pair<short int, short int> arr[], int lo, int hi) {
    if (lo < hi) {
        int pivot = partition(arr, lo, hi);
        quickSort(arr, lo, pivot - 1);
        quickSort(arr, pivot + 1, hi);
    }
}
