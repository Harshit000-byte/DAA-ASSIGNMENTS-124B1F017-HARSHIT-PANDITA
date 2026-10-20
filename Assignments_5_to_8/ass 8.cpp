#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> greedyColoring(const vector<vector<int>>& graph, vector<int> order) {
    int n = graph.size();
    vector<int> color(n, 0);
    for (int u : order) {
        set<int> used;
        for (int v : graph[u]) if (color[v]) used.insert(color[v]);
        int c = 1;
        while (used.count(c)) ++c;
        color[u] = c;
    }
    return color;
}

vector<int> welshPowell(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (graph[a].size() != graph[b].size())
            return graph[a].size() > graph[b].size();
        return a < b;
    });
    return greedyColoring(graph, order);
}

vector<int> dsatur(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, 0);
    vector<int> saturation(n, 0);
    vector<set<int>> neighborColors(n);
    int colored = 0;

    while (colored < n) {
        int chosen = -1;
        for (int u = 0; u < n; ++u) {
            if (color[u] != 0) continue;
            if (chosen == -1 ||
                saturation[u] > saturation[chosen] ||
                (saturation[u] == saturation[chosen] &&
                 graph[u].size() > graph[chosen].size())) {
                chosen = u;
            }
        }

        int c = 1;
        while (neighborColors[chosen].count(c)) ++c;
        color[chosen] = c;
        ++colored;

        for (int v : graph[chosen]) {
            if (color[v] == 0 && neighborColors[v].insert(c).second) {
                saturation[v] = (int)neighborColors[v].size();
            }
        }
    }
    return color;
}

int countColors(const vector<int>& colors) {
    return colors.empty() ? 0 : *max_element(colors.begin(), colors.end());
}

void printSchedule(const string& label, const vector<int>& colors) {
    cout << "\n" << label << " (slots used: " << countColors(colors) << ")\n";
    for (int i = 0; i < (int)colors.size(); ++i) {
        cout << "Course " << i << " -> Slot " << colors[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "UNIVERSITY TIMETABLE: GREEDY, WELSH-POWELL AND DSATUR\n";
    cout << "Enter number of courses and conflict edges: ";
    cin >> n >> m;

    if (!cin || n <= 0 || m < 0) {
        cout << "Invalid input.\n";
        return 1;
    }

    vector<vector<int>> graph(n);
    cout << "Enter conflicting course pairs (IDs 0 to " << n - 1 << "):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (!cin || u < 0 || u >= n || v < 0 || v >= n || u == v) {
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

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    auto greedy = greedyColoring(graph, order);
    auto wp = welshPowell(graph);
    auto ds = dsatur(graph);

    printSchedule("GREEDY COLORING", greedy);
    printSchedule("WELSH-POWELL", wp);
    printSchedule("DSATUR", ds);

    cout << "\nALGORITHM COMPARISON\n";
    cout << "Greedy: simple and fast; result depends on vertex order.\n";
    cout << "Welsh-Powell: colors higher-degree courses first; often reduces conflicts efficiently.\n";
    cout << "DSATUR: repeatedly chooses the uncolored course with the most distinct neighbor colors.\n";
    cout << "All three are heuristics and do not guarantee the globally minimum number of slots.\n";
    cout << "Typical implementation cost: greedy O(V+E) with suitable data structures; Welsh-Powell O(V log V + E); DSATUR depends on selection structures and is commonly O(V^2 + E).\n";

    int rooms;
    cout << "\nEnter number of available rooms for capacity checking (0 to skip): ";
    cin >> rooms;
    if (!cin || rooms < 0) {
        cout << "Invalid room count.\n";
        return 1;
    }

    if (rooms > 0) {
        vector<int> capacity(rooms);
        cout << "Enter capacity of each room:\n";
        for (int &c : capacity) {
            cin >> c;
            if (!cin || c <= 0) {
                cout << "Room capacities must be positive.\n";
                return 1;
            }
        }

        int exams;
        cout << "Enter number of courses requiring room allocation: ";
        cin >> exams;
        if (!cin || exams < 0 || exams > n) {
            cout << "Invalid exam count.\n";
            return 1;
        }

        vector<int> students(n, 0);
        cout << "Enter student count for each course ID (0 to "
             << n - 1 << "):\n";
        for (int &s : students) {
            cin >> s;
            if (!cin || s < 0) {
                cout << "Invalid student count.\n";
                return 1;
            }
        }

        cout << "\nRoom allocation check using DSATUR slots:\n";
        vector<int> roomLoad(countColors(ds), 0);
        for (int i = 0; i < n; ++i) roomLoad[ds[i] - 1] += students[i];

        for (int slot = 0; slot < (int)roomLoad.size(); ++slot) {
            int totalCapacity = accumulate(capacity.begin(), capacity.end(), 0);
            cout << "Slot " << slot + 1 << ": enrolled students = "
                 << roomLoad[slot] << ", total room capacity = "
                 << totalCapacity << " -> "
                 << (roomLoad[slot] <= totalCapacity ? "Capacity sufficient" : "Extra room/capacity needed")
                 << '\n';
        }
        cout << "This is an aggregate capacity check; actual room assignment must also respect each exam's room requirements.\n";
    }

    return 0;
}
