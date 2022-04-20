#pragma once

int partition(pair<short int, short int> arr[], int lo, int hi) {
    int left = lo;
    int pivot = arr[lo].first;

    for (int i = lo + 1; i < hi; i++) {
        if (arr[i].first < pivot) {
            swap(arr[i], arr[left]);
            left++;
        }
    }
    swap(arr[pivot], arr[left]);

    return left;
}

void quickSort(pair<short int, short int> arr[], int lo, int hi) {
    if (lo < hi) {
        int pivot = partition(arr, lo, hi);
        quickSort(arr, lo, pivot);
        quickSort(arr, pivot + 1, hi);
    }
}
