#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Movie {
    string movieId;
    string title;
    double rating;
    int releaseYear;
    int watchTimeMins;
    string genre;
};

// Partition function based on IMDb rating
int partitionMovies(vector<Movie>& arr, int low, int high) {
    double pivot = arr[high].rating;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].rating <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// QuickSort function for movies
void quickSortMovies(vector<Movie>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionMovies(arr, low, high);
        quickSortMovies(arr, low, pivotIndex - 1);
        quickSortMovies(arr, pivotIndex + 1, high);
    }
}

vector<Movie> loadMoviesFromCSV(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);
    if (!file.is_open()) return movies;

    string line, item;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Movie m;
        getline(ss, m.movieId, ',');
        getline(ss, m.title, ',');
        getline(ss, item, ',');
        m.rating = item.empty() ? 0.0 : stod(item);
        getline(ss, item, ',');
        m.releaseYear = item.empty() ? 0 : stoi(item);
        getline(ss, item, ',');
        m.watchTimeMins = item.empty() ? 0 : stoi(item);
        getline(ss, m.genre, ',');
        movies.push_back(m);
    }
    return movies;
}

int main() {
    cout << "========================================================================\n";
    cout << "   Assignment 2: StreamFlix Movie Recommendation System (Quick Sort)\n";
    cout << "   Student: Harshit Pandita | PRN: 124B1F017\n";
    cout << "========================================================================\n\n";

    string csvFile = "Assignment_2_Quick_Sort/movies_dataset.csv";
    vector<Movie> movies = loadMoviesFromCSV(csvFile);
    if (movies.empty()) {
        movies = loadMoviesFromCSV("movies_dataset.csv");
    }

    if (movies.empty()) {
        movies = {
            {"MOV201", "The Dark Knight", 9.0, 2008, 152, "Action/Crime"},
            {"MOV207", "Fast & Furious 9", 6.5, 2021, 143, "Action"},
            {"MOV208", "Red Notice", 7.3, 2021, 118, "Action/Comedy"},
            {"MOV206", "Interstellar Space", 8.2, 2014, 169, "Sci-Fi"},
            {"MOV202", "Inception", 8.7, 2010, 148, "Sci-Fi/Action"}
        };
    }

    cout << "Loaded " << movies.size() << " Movies from StreamFlix Dataset:\n";
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID" << setw(28) << "Title" << setw(10) << "Rating" << setw(8) << "Year" << "Genre\n";
    cout << "------------------------------------------------------------------------\n";
    for (const auto& m : movies) {
        cout << left << setw(10) << m.movieId << setw(28) << m.title << fixed << setprecision(1) << setw(10) << m.rating << setw(8) << m.releaseYear << m.genre << "\n";
    }
    cout << "------------------------------------------------------------------------\n\n";

    quickSortMovies(movies, 0, movies.size() - 1);

    cout << "Movies Sorted by IMDb Rating using Quick Sort:\n";
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID" << setw(28) << "Title" << setw(10) << "Rating" << setw(8) << "Year" << "Genre\n";
    cout << "------------------------------------------------------------------------\n";
    for (const auto& m : movies) {
        cout << left << setw(10) << m.movieId << setw(28) << m.title << fixed << setprecision(1) << setw(10) << m.rating << setw(8) << m.releaseYear << m.genre << "\n";
    }
    cout << "------------------------------------------------------------------------\n";

    return 0;
}
