# Pimpri-Chinchwad Education Trust's
## Pimpri-Chinchwad College of Engineering
*(An Autonomous Institute)*  
*Affiliated to Savitribai Phule Pune University (SPPU) | ISO 21001:2018 Certified by TUV*

---

### **Assignment No 2: Quick Sort**

**Name:** Harshit Pandita  
**PRN:** 124B1F017  
**Subject:** Design and Analysis of Algorithms  
**Batch:** A1  

---

### 1. Problem Statement:
A popular OTT platform, **StreamFlix**, offers personalized recommendations by sorting movies based on user preferences, such as IMDb rating, release year, or watch time popularity. However, during peak hours, sorting large datasets slows down the system. As a backend engineer, you must:
- Implement Quicksort to efficiently sort movies based on various user-selected parameters.
- Handle large datasets containing movies while maintaining fast response times.

### 2. Course Objective:
- To know the basics of computational complexity of various algorithms.
- To select appropriate algorithm design strategies to solve real-world problems.

### 3. Course Outcome:
- Analyze the asymptotic performance of algorithms.
- Solve computational problems by applying suitable paradigms of Divide and Conquer or Greedy methodologies.

### 4. Theory:
Quick Sort is one of the most widely used sorting algorithms because of its efficiency, simplicity in concept, and adaptability. It is based on the divide-and-conquer paradigm, which makes it highly effective in sorting large datasets. Unlike some other sorting algorithms, Quick Sort is an in-place algorithm, meaning it requires very little extra memory, and it avoids the overhead of merging, as seen in Merge Sort.

#### Working of Quick Sort:
- **Divide:** A pivot element is selected from the array. The choice of pivot can significantly affect performance. Common strategies include choosing the last element, the first element, a random element, or using the median-of-three method (the median of the first, middle, and last elements).
- **Partition:** The array is rearranged so that all elements smaller than the pivot are placed to its left and all elements larger are placed to its right. The pivot itself is placed in its correct sorted position.
- **Conquer:** The same process is applied recursively to the left and right subarrays created by the partition step.

Unlike some other divide-and-conquer algorithms, Quick Sort does not require a separate combine step. Once all recursive calls complete, the array is already sorted due to the placement of pivots at each stage. The efficiency of Quick Sort lies in its average-case time complexity of $O(n \log n)$, which makes it suitable for a wide range of applications. However, in the worst case—when the pivot selection is poor and the partitioning is unbalanced—its performance can degrade to $O(n^2)$.

#### Optimizations:
- **Random Pivot Selection:** Choosing a random pivot reduces the chance of encountering consistently unbalanced partitions.
- **Median-of-Three Method:** Using the median of the first, middle, and last elements as the pivot leads to more balanced partitions in practice.
- **Tail Recursion Elimination:** By converting tail-recursive calls into iterative steps, the recursion depth can be reduced, improving space efficiency.
- **Hybrid Approach:** For small subarrays, switching from QuickSort to a simpler algorithm like Insertion Sort can improve performance since the overhead of recursion becomes significant for small input sizes.

---

### 5. Time and Space Complexity

| Case | Time Complexity | Description |
| :--- | :---: | :--- |
| **Best Case** | $O(n \log n)$ | Balanced partitions |
| **Average Case** | $O(n \log n)$ | Typical for random input |
| **Worst Case** | $O(n^2)$ | When pivot is poorly chosen |
| **Space Complexity** | $O(n \log n)$ | For recursive stack calls |

---

### Quick Sort Algorithm & Pseudocode

#### Quick Sort Algorithm
1. Start with an unsorted array.
2. Choose a pivot element (last element, first element, random, or median-of-three).
3. Partition the array so that:
   - All elements smaller than the pivot are placed before it.
   - All elements greater than the pivot are placed after it.
4. Place the pivot in its correct sorted position.
5. Recursively apply QuickSort on the left subarray and right subarray.
6. Continue until subarrays have size 0 or 1 (base case).
7. End when the entire array is sorted.

#### Pseudo code
```text
ALGORITHM QuickSort(arr, low, high)
1. if low < high then
2.     pivotIndex <- Partition(arr, low, high)
3.     // Recursively sort elements before and after partition
4.     QuickSort(arr, low, pivotIndex - 1)
5.     QuickSort(arr, pivotIndex + 1, high)
6. end if
END ALGORITHM

ALGORITHM Partition(arr, low, high)
1. pivot <- arr[high]        // Choose last element as pivot
2. i <- low - 1               // Index of smaller element
3. for j <- low to high - 1 do
4.     if arr[j] <= pivot then
5.         i <- i + 1
6.         SWAP(arr[i], arr[j])
7.     end if
8. end for
9. SWAP(arr[i + 1], arr[high]) // Place pivot at correct position
10. return (i + 1)            // Return pivot index
END ALGORITHM
```

---

### 6. Flow Diagram:
```text
                     +-----------------------+
                     |         Start         |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Prompt user for input /|
                     | Retrieve movie array  |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Print unsorted array  |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Split array into 2    |
                     | batches using pivot   |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Batch size == 1?      |
                     +-----+-----------+-----+
                           |           |
                      Yes  |           | No
                           v           v
            +--------------+-------+ +-+--------------------+
            | Output sorted array   | | Sort each partition |
            +--------------+-------+ | recursively using    |
                           |         | quick sort function  |
                           |         +----------+-----------+
                           |                    |
                           +--------------------+
                                 |
                     +-----------v-----------+
                     |          End          |
                     +-----------------------+
```

---

### 7. Example:
Given Array: `[3, 1, 4, 2]`

- **Step 1: Choose Pivot:** Choose the last element as the pivot. $\text{Pivot} = 2$
- **Step 2: Partition Around Pivot:** Compare each element with pivot 2:
  - $3 > 2 \rightarrow$ goes to the right
  - $1 < 2 \rightarrow$ goes to the left
  - $4 > 2 \rightarrow$ goes to the right  
  After partitioning: `[1, 2, 4, 3]` (Pivot 2 is in correct sorted position).
- **Step 3: Recursive Calls:**
  - Left subarray: `[1]` (already sorted)
  - Right subarray: `[4, 3]`
- **Step 4: Quick Sort on `[4, 3]`:**
  - Pivot = 3
  - Compare $4 > 3 \rightarrow$ goes to right $\rightarrow$ `[3, 4]`
- **Final Sorted Array:** `[1, 2, 3, 4]`

---

### 8. Output:
#### Example Dataset — Movies Sorted by IMDb Rating
Given movie ratings: `[8.2, 6.5, 9.0, 7.3, 8.7]`

- **Step 1: Choose Pivot (8.7)**
  - Elements $\le 8.7 \rightarrow [8.2, 6.5, 7.3]$
  - Elements $> 8.7 \rightarrow [9.0]$
  - After partitioning: `[8.2, 6.5, 7.3, 8.7, 9.0]` (Pivot 8.7 in place)
- **Step 2: Recursively Apply Quick Sort**
  - Left subarray `[8.2, 6.5, 7.3]` (Pivot 7.3):
    - Elements $\le 7.3 \rightarrow [6.5]$
    - Elements $> 7.3 \rightarrow [8.2]$
    - Partitioned: `[6.5, 7.3, 8.2]`
  - Right subarray `[9.0]` (1 element, sorted)
- **Step 3: Combine Results**
  - Combined: `[6.5, 7.3, 8.2] + [8.7] + [9.0]`
  - **Final Output:** `[6.5, 7.3, 8.2, 8.7, 9.0]`

Therefore, the movies are arranged in ascending order of IMDb rating.

---

### 9. GitHub Repository:
[https://github.com/harshitpandita/DAA-Assignments.git](https://github.com/harshitpandita/DAA-Assignments.git)

---

### 10. Conclusion:
Quick Sort is an efficient and memory-friendly algorithm ideal for sorting large movie datasets based on user preferences like rating, release year, or popularity. By using Quick Sort, StreamFlix can ensure fast and responsive recommendations even during peak hours, improving performance and user experience.
