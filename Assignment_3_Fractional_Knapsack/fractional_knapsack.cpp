#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    string name;
    double weight;
    double utility;
    bool isDivisible;
    double ratio;
};

// Comparator to sort items by utility-to-weight ratio in descending order
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

double getOptimalReliefUtility(vector<Item>& items, double capacity) {
    // Compute ratio for each item
    for (auto& item : items) {
        item.ratio = item.utility / item.weight;
    }

    // Sort in descending order of ratio
    sort(items.begin(), items.end(), compareItems);

    double totalUtility = 0.0;
    double remainingCapacity = capacity;

    cout << "Sorted Preference Order (High to Low Utility/Weight Ratio):\n";
    cout << "--------------------------------------------------------\n";
    for (const auto& item : items) {
        cout << "- " << left << setw(10) << item.name 
             << " | Weight: " << setw(5) << item.weight << " kg"
             << " | Utility: " << setw(5) << item.utility
             << " | Ratio: " << fixed << setprecision(2) << item.ratio << " per kg\n";
    }
    cout << "--------------------------------------------------------\n\n";

    cout << "Filling Boat (Capacity: " << capacity << " kg):\n";

    for (const auto& item : items) {
        if (remainingCapacity == 0) {
            break;
        }

        if (item.weight <= remainingCapacity) {
            totalUtility += item.utility;
            remainingCapacity -= item.weight;
            cout << "-> Taken FULL  : " << left << setw(10) << item.name 
                 << " (Weight used: " << item.weight << " kg, Utility added: " << item.utility 
                 << ", Remaining boat capacity: " << remainingCapacity << " kg)\n";
        } else if (item.isDivisible) {
            double fraction = remainingCapacity / item.weight;
            double utilityAdded = item.utility * fraction;
            totalUtility += utilityAdded;
            cout << "-> Taken PARTIAL: " << left << setw(10) << item.name 
                 << " (Weight used: " << remainingCapacity << " kg [" << fraction*100 << "%], Utility added: " 
                 << utilityAdded << ", Remaining boat capacity: 0 kg)\n";
            remainingCapacity = 0;
        } else {
            cout << "-> SKIPPED     : " << left << setw(10) << item.name 
                 << " (Cannot fit full indivisible item)\n";
        }
    }

    return totalUtility;
}

int main() {
    cout << "========================================================================\n";
    cout << " Assignment 3: Fractional Knapsack Emergency Relief Supply Distribution\n";
    cout << " Student: Harshit Pandita | PRN: 124B1F017\n";
    cout << "========================================================================\n\n";

    vector<Item> items = {
        {"Medicine", 5.0, 50.0, false, 0.0},
        {"Food",     10.0, 30.0, true,  0.0},
        {"Water",    20.0, 20.0, true,  0.0}
    };

    double boatCapacity = 17.0;

    double maxUtility = getOptimalReliefUtility(items, boatCapacity);

    cout << "\n========================================================\n";
    cout << " Total Utility Value Obtained = " << maxUtility << "\n";
    cout << "========================================================\n";

    return 0;
}
