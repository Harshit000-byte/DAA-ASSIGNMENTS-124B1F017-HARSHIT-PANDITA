#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;

struct Edge {
    int to;
    long long cost;
};

struct RouteResult {
    long long totalCost;
    vector<int> path;
};

class SwiftCargoNetwork {
private:
    int n;
    vector<vector<Edge>> graph;
    vector<int> stage;

public:
    SwiftCargoNetwork(int cities, vector<int> cityStages)
        : n(cities), graph(cities), stage(std::move(cityStages)) {}

    void addRoute(int from, int to, long long cost) {
        // Always add a new edge: parallel routes between the same cities
        // are supported, making this a directed weighted multigraph.
        graph[from].push_back({to, cost});
    }

    bool updateRouteCost(int from, int to, long long cost) {
        // Update the first matching directed route.
        for (auto &edge : graph[from]) {
            if (edge.to == to) {
                edge.cost = cost;
                return true;
            }
        }
        return false;
    }

    RouteResult shortestRoute(int source, int destination) const {
        vector<long long> dist(n, INF);
        vector<int> parent(n, -1);

        // Dijkstra is suitable because all route costs must be non-negative.
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [currentCost, u] = pq.top();
            pq.pop();

            if (currentCost != dist[u]) continue;
            if (u == destination) break;

            for (const auto &edge : graph[u]) {
                int v = edge.to;
                long long nextCost = currentCost + edge.cost;

                if (nextCost < dist[v]) {
                    dist[v] = nextCost;
                    parent[v] = u;
                    pq.push({nextCost, v});
                }
            }
        }

        if (dist[destination] == INF) return {INF, {}};

        vector<int> path;
        for (int cur = destination; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
            if (cur == source) break;
        }

        if (path.back() != source) return {INF, {}};
        reverse(path.begin(), path.end());

        // Ensure the route follows the multistage order.
        for (size_t i = 1; i < path.size(); ++i) {
            if (stage[path[i]] <= stage[path[i - 1]]) {
                return {INF, {}};
            }
        }

        return {dist[destination], path};
    }

    void processBatch(const vector<pair<int, int>> &requests) const {
        cout << "\nBATCH DELIVERY ROUTES\n";
        cout << "===============================================\n";

        for (size_t i = 0; i < requests.size(); ++i) {
            int source = requests[i].first;
            int destination = requests[i].second;
            RouteResult result = shortestRoute(source, destination);

            cout << "Request " << i + 1 << ": City " << source
                 << " -> City " << destination << '\n';

            if (result.path.empty()) {
                cout << "Status: No valid multistage route available.\n";
                continue;
            }

            cout << "Optimal route: ";
            for (size_t j = 0; j < result.path.size(); ++j) {
                cout << "City " << result.path[j];
                if (j + 1 < result.path.size()) cout << " -> ";
            }
            cout << "\nTotal cost/time: " << result.totalCost << '\n';
        }

        cout << "===============================================\n";
    }

    void closeRoute(int from, int to) {
        auto &edges = graph[from];
        edges.erase(
            remove_if(edges.begin(), edges.end(),
                      [to](const Edge &edge) { return edge.to == to; }),
            edges.end()
        );
    }

    int size() const {
        return n;
    }

    int getStage(int city) const {
        return stage[city];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "SWIFTCARGO MULTISTAGE LOGISTICS ROUTE OPTIMIZER\n";

    int n, m, numberOfStages;
    cout << "Enter number of cities, routes, and stages: ";
    cin >> n >> m >> numberOfStages;

    if (!cin || n <= 0 || m < 0 || numberOfStages < 2) {
        cout << "Invalid graph configuration.\n";
        return 1;
    }

    vector<int> stages(n);
    cout << "Enter the stage number for each city (0 to "
         << numberOfStages - 1 << "):\n";

    for (int i = 0; i < n; ++i) {
        cin >> stages[i];
        if (!cin || stages[i] < 0 || stages[i] >= numberOfStages) {
            cout << "Invalid stage number.\n";
            return 1;
        }
    }

    SwiftCargoNetwork network(n, stages);

    cout << "Enter each directed route as: from_city to_city cost_or_time\n";
    cout << "Route costs must be non-negative and routes must go to a later stage.\n";

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long cost;
        cin >> u >> v >> cost;

        if (!cin || u < 0 || u >= n || v < 0 || v >= n ||
            cost < 0 || stages[v] <= stages[u]) {
            cout << "Invalid route. Check city IDs, cost, and stage order.\n";
            return 1;
        }

        network.addRoute(u, v, cost);
    }

    int requestCount;
    cout << "Enter number of delivery requests for batch processing: ";
    cin >> requestCount;

    if (!cin || requestCount <= 0) {
        cout << "At least one delivery request is required.\n";
        return 1;
    }

    vector<pair<int, int>> requests(requestCount);
    cout << "Enter each request as: source_city destination_city\n";

    for (auto &request : requests) {
        cin >> request.first >> request.second;

        if (!cin || request.first < 0 || request.first >= n ||
            request.second < 0 || request.second >= n ||
            stages[request.first] >= stages[request.second]) {
            cout << "Invalid delivery request.\n";
            return 1;
        }
    }

    network.processBatch(requests);

    while (true) {
        cout << "\nMENU\n";
        cout << "1. Update route cost/time\n";
        cout << "2. Mark a route as closed\n";
        cout << "3. Recalculate all batch routes\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (!cin) break;

        if (choice == 1) {
            int u, v;
            long long newCost;
            cout << "Enter route (from_city to_city new_cost): ";
            cin >> u >> v >> newCost;

            if (!cin || u < 0 || u >= n || v < 0 || v >= n ||
                newCost < 0 || stages[v] <= stages[u]) {
                cout << "Invalid route update.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (!network.updateRouteCost(u, v, newCost)) {
                cout << "No such directed route exists; update was not applied.\n";
                continue;
            }
            cout << "Route cost/time updated.\n";
            network.processBatch(requests);
        } else if (choice == 2) {
            int u, v;
            cout << "Enter directed route to close (from_city to_city): ";
            cin >> u >> v;

            if (!cin || u < 0 || u >= n || v < 0 || v >= n) {
                cout << "Invalid city IDs.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            network.closeRoute(u, v);
            cout << "Route marked closed for optimization purposes.\n";
            network.processBatch(requests);
        } else if (choice == 3) {
            network.processBatch(requests);
        } else if (choice == 4) {
            cout << "SwiftCargo route optimizer closed.\n";
            break;
        } else {
            cout << "Invalid choice. Select 1, 2, 3, or 4.\n";
        }
    }

    return 0;
}
