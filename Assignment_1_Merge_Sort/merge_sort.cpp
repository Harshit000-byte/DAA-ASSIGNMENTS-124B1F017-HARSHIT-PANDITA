#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to merge two sorted subarrays
void merge(vector<string>& arr, int low, int mid, int high) {
    vector<string> temp;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= high) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        arr[low + k] = temp[k];
    }
}

// Function to perform Merge Sort
void mergeSort(vector<string>& arr, int low, int high) {
    if (low >= high) {
        return;
    }
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main() {
    cout << "========================================================\n";
    cout << "       Assignment 1: Customer Order Sorting (Merge Sort)\n";
    cout << "       Student: Harshit Pandita | PRN: 124B1F017\n";
    cout << "========================================================\n\n";

    vector<string> timestamps = {"12:30", "09:15", "14:45", "10:00"};

    cout << "Input Customer Order Timestamps:\n[";
    for (size_t i = 0; i < timestamps.size(); i++) {
        cout << timestamps[i] << (i == timestamps.size() - 1 ? "" : ", ");
    }
    cout << "]\n\n";

    mergeSort(timestamps, 0, timestamps.size() - 1);

    cout << "Orders sorted by timestamp:\n[";
    for (size_t i = 0; i < timestamps.size(); i++) {
        cout << timestamps[i] << (i == timestamps.size() - 1 ? "" : ", ");
    }
    cout << "]\n";

    return 0;
}
