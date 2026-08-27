#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Order {
    string orderId;
    string customerName;
    string timestamp;
    double amount;
    string status;
};

// Merge function for Order structs based on timestamp
void mergeOrders(vector<Order>& arr, int low, int mid, int high) {
    vector<Order> temp;
    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        if (arr[i].timestamp <= arr[j].timestamp) {
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

// Recursive Merge Sort function
void mergeSortOrders(vector<Order>& arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSortOrders(arr, low, mid);
    mergeSortOrders(arr, mid + 1, high);
    mergeOrders(arr, low, mid, high);
}

vector<Order> loadOrdersFromCSV(const string& filename) {
    vector<Order> orders;
    ifstream file(filename);
    if (!file.is_open()) return orders;

    string line, item;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Order ord;
        getline(ss, ord.orderId, ',');
        getline(ss, ord.customerName, ',');
        getline(ss, ord.timestamp, ',');
        getline(ss, item, ',');
        ord.amount = item.empty() ? 0.0 : stod(item);
        getline(ss, ord.status, ',');
        orders.push_back(ord);
    }
    return orders;
}

int main() {
    cout << "========================================================================\n";
    cout << "       Assignment 1: Customer Order Sorting (Merge Sort)\n";
    cout << "       Student: Harshit Pandita | PRN: 124B1F017\n";
    cout << "========================================================================\n\n";

    string csvFile = "Assignment_1_Merge_Sort/orders_dataset.csv";
    vector<Order> orders = loadOrdersFromCSV(csvFile);
    if (orders.empty()) {
        orders = loadOrdersFromCSV("orders_dataset.csv");
    }

    if (orders.empty()) {
        // Fallback default dataset
        orders = {
            {"ORD1001", "Amit Sharma", "12:30", 1499.0, "Delivered"},
            {"ORD1002", "Priya Patel", "09:15", 850.5, "Processing"},
            {"ORD1003", "Rahul Verma", "14:45", 3200.0, "Shipped"},
            {"ORD1004", "Sneha Kulkarni", "10:00", 450.0, "Delivered"}
        };
    }

    cout << "Loaded " << orders.size() << " Customer Orders from Dataset:\n";
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Order ID" << setw(18) << "Customer Name" << setw(12) << "Timestamp" << setw(14) << "Amount (INR)" << "Status\n";
    cout << "------------------------------------------------------------------------\n";
    for (const auto& ord : orders) {
        cout << left << setw(10) << ord.orderId << setw(18) << ord.customerName << setw(12) << ord.timestamp << "Rs. " << setw(10) << fixed << setprecision(2) << ord.amount << ord.status << "\n";
    }
    cout << "------------------------------------------------------------------------\n\n";

    mergeSortOrders(orders, 0, orders.size() - 1);

    cout << "Orders Sorted by Timestamp using Merge Sort (Divide & Conquer):\n";
    cout << "------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Order ID" << setw(18) << "Customer Name" << setw(12) << "Timestamp" << setw(14) << "Amount (INR)" << "Status\n";
    cout << "------------------------------------------------------------------------\n";
    for (const auto& ord : orders) {
        cout << left << setw(10) << ord.orderId << setw(18) << ord.customerName << setw(12) << ord.timestamp << "Rs. " << setw(10) << fixed << setprecision(2) << ord.amount << ord.status << "\n";
    }
    cout << "------------------------------------------------------------------------\n";

    return 0;
}
