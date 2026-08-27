#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Partition function using last element as pivot
int partition(vector<double>& arr, int low, int high) {
    double pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// QuickSort function
void quickSort(vector<double>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    cout << "========================================================\n";
    cout << "   Assignment 2: StreamFlix Movie Ratings (Quick Sort)\n";
    cout << "   Student: Harshit Pandita | PRN: 124B1F017\n";
    cout << "========================================================\n\n";

    vector<double> ratings = {8.2, 6.5, 9.0, 7.3, 8.7};

    cout << "Given Movie IMDb Ratings:\n[";
    for (size_t i = 0; i < ratings.size(); i++) {
        cout << fixed << setprecision(1) << ratings[i] << (i == ratings.size() - 1 ? "" : ", ");
    }
    cout << "]\n\n";

    quickSort(ratings, 0, ratings.size() - 1);

    cout << "Movies sorted efficiently by IMDb Rating:\n[";
    for (size_t i = 0; i < ratings.size(); i++) {
        cout << fixed << setprecision(1) << ratings[i] << (i == ratings.size() - 1 ? "" : ", ");
    }
    cout << "]\n";

    return 0;
}
