#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Item {
    string name;
    int weight;
    int utility;
    bool perishable;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, capacity;
    cout << "DISASTER RELIEF RESOURCE ALLOCATION - 0/1 KNAPSACK\n";
    cout << "Enter number of item types and truck capacity (kg): ";
    cin >> n >> capacity;

    if (!cin || n <= 0 || capacity < 0) {
        cout << "Invalid input.\n";
        return 1;
    }

    vector<Item> items(n);
    cout << "Enter each item: name weight_kg utility perishable(1=yes, 0=no)\n";
    for (auto &item : items) {
        cin >> item.name >> item.weight >> item.utility >> item.perishable;
        if (!cin || item.weight < 0 || item.utility < 0) {
            cout << "Invalid item data.\n";
            return 1;
        }
    }

    // dp[i][w] stores the best utility using the first i items and capacity w.
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].utility);
            }
        }
    }

    vector<int> selected;
    int remaining = capacity;
    for (int i = n; i > 0; --i) {
        if (dp[i][remaining] != dp[i - 1][remaining]) {
            selected.push_back(i - 1);
            remaining -= items[i - 1].weight;
        }
    }
    reverse(selected.begin(), selected.end());

    int totalWeight = 0, totalUtility = 0;
    cout << "\nOPTIMAL LOAD\n";
    cout << "---------------------------------------------\n";
    for (int index : selected) {
        cout << items[index].name << " | Weight: " << items[index].weight
             << " kg | Utility: " << items[index].utility;
        if (items[index].perishable) cout << " | Perishable/priority";
        cout << '\n';
        totalWeight += items[index].weight;
        totalUtility += items[index].utility;
    }

    cout << "---------------------------------------------\n";
    cout << "Total weight: " << totalWeight << " kg / " << capacity << " kg\n";
    cout << "Maximum utility: " << totalUtility << '\n';

    cout << "\nAPPROACH COMPARISON\n";
    cout << "Brute force: O(2^N) time; tests every subset.\n";
    cout << "Dynamic programming: O(N * W) time and O(N * W) memory.\n";
    cout << "Greedy by utility/weight: usually O(N log N), but is not guaranteed optimal for 0/1 knapsack.\n";
    cout << "Perishable items are identified for planning; utility scores should include urgency to prioritize them.\n";
    cout << "For multiple trucks, solve as a multi-knapsack/assignment problem; for changing supplies, rerun DP after updates.\n";
    return 0;
}
