# Design and Analysis of Algorithms (DAA) - Lab Assignments

**Student Name:** Harshit Pandita  
**PRN:** 124B1F017  
**Institute:** Pimpri-Chinchwad College of Engineering (PCCOE)  
**Subject:** Design and Analysis of Algorithms  
**Batch:** A1  

---

## 📌 Repository Overview
This repository contains the complete lab assignments, problem descriptions, and C++ source code implementations for the Design and Analysis of Algorithms (DAA) coursework.

---

## 📂 Summary of Assignments

### 1. Assignment 1: Merge Sort
- **Topic:** Customer order timestamp sorting using Divide and Conquer Merge Sort.
- **Key Concepts:** Divide and Conquer paradigm, $O(n \log n)$ time complexity across all cases, stable sorting, recursion tree analysis.
- **Folder:** [`Assignment_1_Merge_Sort/`](./Assignment_1_Merge_Sort/)
- **Code:** `merge_sort.cpp`
- **Documentation:** `Assignment_1_Merge_Sort.md`

### 2. Assignment 2: Quick Sort
- **Topic:** StreamFlix Movie Recommendation System sorting movies by IMDb rating.
- **Key Concepts:** Divide and Conquer, Lomuto Partitioning, in-place sorting, pivot selection strategies, $O(n \log n)$ average time complexity.
- **Folder:** [`Assignment_2_Quick_Sort/`](./Assignment_2_Quick_Sort/)
- **Code:** `quick_sort.cpp`
- **Documentation:** `Assignment_2_Quick_Sort.md`

### 3. Assignment 3: Fractional Knapsack
- **Topic:** Emergency Relief Supply Distribution using Greedy Strategy.
- **Key Concepts:** Greedy choice property, value-to-weight ratio ordering, optimal substructure, partial item selection, $O(n \log n)$ complexity.
- **Folder:** [`Assignment_3_Fractional_Knapsack/`](./Assignment_3_Fractional_Knapsack/)
- **Code:** `fractional_knapsack.cpp`
- **Documentation:** `Assignment_3_Fractional_Knapsack.md`

### 4. Assignment 4: Dijkstra's Algorithm
- **Topic:** Smart Traffic Management for Emergency Ambulance Routing.
- **Key Concepts:** Single-source shortest path, greedy relaxation, min-priority queue, dynamic weight handling, $O((V + E) \log V)$ time complexity.
- **Folder:** [`Assignment_4_Dijkstra/`](./Assignment_4_Dijkstra/)
- **Code:** `dijkstra.cpp`
- **Documentation:** `Assignment_4_Dijkstra.md`

### 5. Assignment 5: Multistage Graph
- **Topic:** SwiftCargo Multi-stage Logistics & Transportation Network Optimization.
- **Key Concepts:** Dynamic Programming (backward approach), directed acyclic multistage graphs (DAG), optimal substructure, $O(V + E)$ time complexity.
- **Folder:** [`Assignment-5/`](./Assignment-5/)
- **Code:** `multistage_graph.cpp`
- **Documentation:** `README.md`

### 6. Assignment 6: 0/1 Knapsack (Disaster Relief)
- **Topic:** Disaster Relief Resource Allocation under limited truck capacity.
- **Key Concepts:** Dynamic Programming tabulation, $O(N \cdot W)$ pseudo-polynomial time complexity, subset state tracking, traceback reconstruction.
- **Folder:** [`Assignment-6/`](./Assignment-6/)
- **Code:** `knapsack_01.cpp`
- **Documentation:** `README.md`

### 7. Assignment 7: University Timetable Scheduling
- **Topic:** Conflict-free Exam Timetable & Classroom Allocation.
- **Key Concepts:** Graph Colouring, Chromatic Number, Greedy Coloring / Welsh-Powell / DSATUR heuristics, multi-constraint room capacity allocation.
- **Folder:** [`Assignment-7/`](./Assignment-7/)
- **Code:** `graph_colouring.cpp`
- **Documentation:** `README.md`

### 8. Assignment 8: Travelling Salesman Problem (TSP)
- **Topic:** SwiftShip Delivery Route Optimization visiting every city once.
- **Key Concepts:** Least Cost (LC) Branch & Bound, State Space Tree, Cost Matrix Reduction, lower bound calculation, best-first search using Priority Queue.
- **Folder:** [`Assignment-8/`](./Assignment-8/)
- **Code:** `tsp_branch_bound.cpp`
- **Documentation:** `README.md`

---

## 🚀 How to Run the Programs

Compile and run any of the C++ code files using `g++`:

```bash
# Assignment 1: Merge Sort
g++ -std=c++11 Assignment_1_Merge_Sort/merge_sort.cpp -o merge_sort
./merge_sort

# Assignment 2: Quick Sort
g++ -std=c++11 Assignment_2_Quick_Sort/quick_sort.cpp -o quick_sort
./quick_sort

# Assignment 3: Fractional Knapsack
g++ -std=c++11 Assignment_3_Fractional_Knapsack/fractional_knapsack.cpp -o fractional_knapsack
./fractional_knapsack

# Assignment 4: Dijkstra's Algorithm
g++ -std=c++11 Assignment_4_Dijkstra/dijkstra.cpp -o dijkstra
./dijkstra

# Assignment 5: Multistage Graph
g++ -std=c++11 Assignment-5/multistage_graph.cpp -o multistage_graph
./multistage_graph

# Assignment 6: 0/1 Knapsack
g++ -std=c++11 Assignment-6/knapsack_01.cpp -o knapsack_01
./knapsack_01

# Assignment 7: University Timetable Scheduling
g++ -std=c++11 Assignment-7/graph_colouring.cpp -o graph_colouring
./graph_colouring

# Assignment 8: Travelling Salesman Problem (LC Branch & Bound)
g++ -std=c++11 Assignment-8/tsp_branch_bound.cpp -o tsp_branch_bound
./tsp_branch_bound
