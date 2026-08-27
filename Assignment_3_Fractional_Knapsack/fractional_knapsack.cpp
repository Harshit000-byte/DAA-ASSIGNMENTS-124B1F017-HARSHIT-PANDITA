#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

vector<Item> loadSuppliesFromCSV(const string& filename) {
    vector<Item> items;
    ifstream file(filename);
    if (!file.is_open()) return items;

    string line, item;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Item it;
        getline(ss, it.name, ',');
        getline(ss, item, ',');
        it.weight = item.empty() ? 0.0 : stod(item);
        getline(ss, item, ',');
        it.utility = item.empty() ? 0.0 : stod(item);
        getline(ss, item, ',');
        it.isDivisible = (item == "1" || item == "true" || item == "TRUE");
        it.ratio = 0.0;
        items.push_back(it);
    }
    return items;
}

double solveFractionalKnapsack(vector<Item>& items, double capacity) {
    for (auto& item : items) {
        item.ratio = item.utility / item.weight;
    }

    sort(items.begin(), items.end(), compareItems);

    double totalUtility = 0.0;
    double remainingCapacity = capacity;

    cout << "Sorted Item Ratios (Greedy Preference Order):\n";
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(18) << "Item Name" << setw(14) << "Weight (kg)" << setw(16) << "Utility Value" << setw(14) << "Ratio (V/W)" << "Divisible?\n";
    cout << "------------------------------------------------------------------------\n";
    for (const auto& item : items) {
        cout << left << setw(18) << item.name 
             << setw(14) << fixed << setprecision(2) << item.weight 
             << setw(16) << item.utility 
             << setw(14) << item.ratio 
             << (item.isDivisible ? "Yes (Partial)" : "No (Whole)") << "\n";
    }
    cout << "------------------------------------------------------------------------\n\n";

    cout << "Allocation Process for Rescue Boat (Capacity: " << capacity << " kg):\n";
    cout << "------------------------------------------------------------------------\n";

    for (const auto& item : items) {
        if (remainingCapacity <= 0) break;

        if (item.weight <= remainingCapacity) {
            totalUtility += item.utility;
            remainingCapacity -= item.weight;
            cout << "[FULL SELECTION]  " << left << setw(16) << item.name 
                 << " Weight used: " << setw(6) << item.weight << " kg | Utility: +" << setw(6) << item.utility 
                 << " | Rem. Capacity: " << remainingCapacity << " kg\n";
        } else if (item.isDivisible) {
            double fraction = remainingCapacity / item.weight;
            double utilityAdded = item.utility * fraction;
            totalUtility += utilityAdded;
            cout << "[PARTIAL SELECT] " << left << setw(16) << item.name 
                 << " Weight used: " << setw(6) << remainingCapacity << " kg (" << fixed << setprecision(1) << fraction * 100 << "%) | Utility: +" << setprecision(2) << utilityAdded 
                 << " | Rem. Capacity: 0.00 kg\n";
            remainingCapacity = 0;
        } else {
            cout << "[SKIPPED ITEM]   " << left << setw(16) << item.name 
                 << " (Requires " << item.weight << " kg, but only " << remainingCapacity << " kg capacity remains)\n";
        }
    }
    cout << "------------------------------------------------------------------------\n";
    return totalUtility;
}

int main() {
    cout << "========================================================================\n";
    cout << " Assignment 3: Fractional Knapsack Emergency Relief Supply Distribution\n";
    cout << " Student: Harshit Pandita | PRN: 124B1F017\n";
    cout << "========================================================================\n\n";

    string csvFile = "Assignment_3_Fractional_Knapsack/relief_supplies.csv";
    vector<Item> items = loadSuppliesFromCSV(csvFile);
    if (items.empty()) {
        items = loadSuppliesFromCSV("relief_supplies.csv");
    }

    if (items.empty()) {
        items = {
            {"Medicine", 5.0, 50.0, false, 0.0},
            {"Food", 10.0, 30.0, true, 0.0},
            {"Water", 20.0, 20.0, true, 0.0}
        };
    }

    double boatCapacity = 17.0;
    double maxUtility = solveFractionalKnapsack(items, boatCapacity);

    cout << "\n========================================================\n";
    cout << " Total Utility Value Transported = " << fixed << setprecision(2) << maxUtility << "\n";
    cout << "========================================================\n";

    return 0;
}
