#pragma once

int partition(int* arr, int lo, int hi) {
    int left = lo;
    int pivot = arr[lo];

    for (int i = lo + 1; i < hi; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[left]);
            left++;
        }
    }
    swap(arr[pivot], arr[left]);

    return left;
}

void quickSort(int* arr, int lo, int hi) {
    if (lo < hi) {
        int pivot = partition(arr, lo, hi);
        quickSort(arr, lo, pivot);
        quickSort(arr, pivot + 1, hi);
    }
}