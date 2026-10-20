#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <iomanip>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

struct Edge {
    int to;
    long long time;
};

struct Result {
    vector<long long> dist;
    vector<int> parent;
};

class TrafficNetwork {
private:
    int n;
    vector<vector<Edge>> adj;

public:
    explicit TrafficNetwork(int intersections) : n(intersections), adj(intersections) {}

    void addOrUpdateRoad(int u, int v, long long time) {
        auto update = [&](int from, int to) {
            for (auto &edge : adj[from]) {
                if (edge.to == to) {
                    edge.time = time;
                    return;
                }
            }
            adj[from].push_back({to, time});
        };

        update(u, v);
        update(v, u); // Roads are assumed to be bidirectional.
    }

    Result dijkstra(int source) const {
        Result result;
        result.dist.assign(n, INF);
        result.parent.assign(n, -1);

        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        result.dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [currentTime, u] = pq.top();
            pq.pop();

            if (currentTime != result.dist[u]) {
                continue; // Ignore outdated priority-queue entries.
            }

            for (const auto &edge : adj[u]) {
                int v = edge.to;
                long long newTime = currentTime + edge.time;

                if (newTime < result.dist[v]) {
                    result.dist[v] = newTime;
                    result.parent[v] = u;
                    pq.push({newTime, v});
                }
            }
        }

        return result;
    }

    vector<int> getPath(int source, int destination,
                        const vector<int> &parent) const {
        vector<int> path;

        if (source == destination) {
            path.push_back(source);
            return path;
        }

        if (parent[destination] == -1) {
            return path; // Destination is unreachable.
        }

        for (int current = destination; current != -1;
             current = parent[current]) {
            path.push_back(current);
            if (current == source) {
                break;
            }
        }

        if (path.back() != source) {
            return {};
        }

        reverse(path.begin(), path.end());
        return path;
    }

    void displayPath(const vector<int> &path) const {
        if (path.empty()) {
            cout << "No route available.\n";
            return;
        }

        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i + 1 < path.size()) {
                cout << " -> ";
            }
        }
        cout << '\n';
    }

    void showHospitalRoutes(int source, const vector<int> &hospitals) const {
        Result result = dijkstra(source);

        cout << "\nShortest travel times from intersection " << source << ":\n";
        cout << "-----------------------------------------------\n";

        int nearestHospital = -1;
        long long minimumTime = INF;

        for (int hospital : hospitals) {
            cout << "Hospital " << hospital << ": ";

            if (result.dist[hospital] == INF) {
                cout << "Unreachable\n";
                continue;
            }

            cout << result.dist[hospital] << " minute(s)\n";

            if (result.dist[hospital] < minimumTime) {
                minimumTime = result.dist[hospital];
                nearestHospital = hospital;
            }
        }

        cout << "-----------------------------------------------\n";

        if (nearestHospital == -1) {
            cout << "No hospital is reachable from the ambulance location.\n";
            return;
        }

        vector<int> path = getPath(source, nearestHospital, result.parent);

        cout << "Nearest hospital: " << nearestHospital << '\n';
        cout << "Minimum travel time: " << minimumTime << " minute(s)\n";
        cout << "Recommended route: ";
        displayPath(path);
    }

    int size() const {
        return n;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "SMART TRAFFIC MANAGEMENT FOR EMERGENCY VEHICLES\n";
    cout << "Enter number of intersections and roads: ";
    cin >> n >> m;

    if (!cin || n <= 0 || m < 0) {
        cout << "Invalid number of intersections or roads.\n";
        return 1;
    }

    TrafficNetwork city(n);

    cout << "Enter each road as: intersection1 intersection2 travel_time\n";
    cout << "Use intersection IDs from 0 to " << n - 1
         << ". Travel times must be non-negative.\n";

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long time;
        cin >> u >> v >> time;

        if (!cin || u < 0 || u >= n || v < 0 || v >= n || time < 0) {
            cout << "Invalid road input. Restart the program with valid data.\n";
            return 1;
        }

        city.addOrUpdateRoad(u, v, time);
    }

    int source;
    cout << "Enter ambulance source intersection: ";
    cin >> source;

    if (!cin || source < 0 || source >= n) {
        cout << "Invalid source intersection.\n";
        return 1;
    }

    int hospitalCount;
    cout << "Enter number of hospitals: ";
    cin >> hospitalCount;

    if (!cin || hospitalCount <= 0) {
        cout << "Hospital count must be at least 1.\n";
        return 1;
    }

    vector<int> hospitals(hospitalCount);
    cout << "Enter hospital intersection IDs:\n";

    for (int &hospital : hospitals) {
        cin >> hospital;
        if (!cin || hospital < 0 || hospital >= n) {
            cout << "Invalid hospital intersection.\n";
            return 1;
        }
    }

    city.showHospitalRoutes(source, hospitals);

    while (true) {
        cout << "\nMenu\n";
        cout << "1. Update traffic time on a road\n";
        cout << "2. Recalculate routes using current traffic\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (!cin) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        if (choice == 1) {
            int u, v;
            long long newTime;

            cout << "Enter road endpoints and new travel time: ";
            cin >> u >> v >> newTime;

            if (!cin || u < 0 || u >= n || v < 0 || v >= n ||
                newTime < 0) {
                cout << "Invalid update. Use valid intersections and a "
                        "non-negative travel time.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            city.addOrUpdateRoad(u, v, newTime);
            cout << "Traffic time updated. Recalculating routes...\n";
            city.showHospitalRoutes(source, hospitals);
        } else if (choice == 2) {
            city.showHospitalRoutes(source, hospitals);
        } else if (choice == 3) {
            cout << "Emergency traffic system closed.\n";
            break;
        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}
