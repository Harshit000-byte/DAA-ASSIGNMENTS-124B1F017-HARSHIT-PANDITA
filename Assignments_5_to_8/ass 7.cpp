#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool safeColor(int course, int color, const vector<vector<int>>& graph,
               const vector<int>& colors) {
    for (int neighbor : graph[course]) {
        if (colors[neighbor] == color) return false;
    }
    return true;
}

bool colorBacktracking(int course, int maxColors,
                       const vector<vector<int>>& graph,
                       vector<int>& colors) {
    if (course == (int)graph.size()) return true;

    for (int color = 1; color <= maxColors; ++color) {
        if (safeColor(course, color, graph, colors)) {
            colors[course] = color;
            if (colorBacktracking(course + 1, maxColors, graph, colors)) return true;
            colors[course] = 0;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int courses, conflicts;
    cout << "UNIVERSITY EXAM TIMETABLE - GRAPH COLORING\n";
    cout << "Enter number of courses and conflict edges: ";
    cin >> courses >> conflicts;

    if (!cin || courses <= 0 || conflicts < 0) {
        cout << "Invalid input.\n";
        return 1;
    }

    vector<vector<int>> graph(courses);
    cout << "Enter each conflicting course pair (course IDs 0 to "
         << courses - 1 << "):\n";

    for (int i = 0; i < conflicts; ++i) {
        int u, v;
        cin >> u >> v;
        if (!cin || u < 0 || u >= courses || v < 0 || v >= courses || u == v) {
            cout << "Invalid conflict pair.\n";
            return 1;
        }
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (auto &neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }

    vector<int> greedyColors(courses, 0);
    int greedyCount = 0;
    for (int u = 0; u < courses; ++u) {
        set<int> used;
        for (int v : graph[u]) {
            if (greedyColors[v] != 0) used.insert(greedyColors[v]);
        }
        int color = 1;
        while (used.count(color)) ++color;
        greedyColors[u] = color;
        greedyCount = max(greedyCount, color);
    }

    cout << "\nGREEDY COLORING SCHEDULE\n";
    cout << "Course -> Exam slot\n";
    for (int i = 0; i < courses; ++i) {
        cout << i << " -> Slot " << greedyColors[i] << '\n';
    }
    cout << "Greedy slots used: " << greedyCount << '\n';

    // Backtracking searches for the smallest number of colors.
    vector<int> exactColors(courses, 0);
    int minimumColors = 1;
    for (; minimumColors <= greedyCount; ++minimumColors) {
        fill(exactColors.begin(), exactColors.end(), 0);
        if (colorBacktracking(0, minimumColors, graph, exactColors)) break;
    }

    cout << "\nBACKTRACKING RESULT\n";
    cout << "Minimum slots found: " << minimumColors << '\n';
    for (int i = 0; i < courses; ++i) {
        cout << "Course " << i << " -> Slot " << exactColors[i] << '\n';
    }

    cout << "\nComplexity notes:\n";
    cout << "Greedy coloring is efficient and typically practical for large graphs.\n";
    cout << "Backtracking can find a minimum coloring but has exponential worst-case time.\n";
    cout << "For thousands of courses, prefer heuristics such as DSATUR or Welsh-Powell.\n";
    cout << "Room capacity must be checked separately for courses assigned to the same slot.\n";
    return 0;
}
