# Pimpri-Chinchwad Education Trust's
## Pimpri-Chinchwad College of Engineering
*(An Autonomous Institute)*  
*Affiliated to Savitribai Phule Pune University (SPPU) | ISO 21001:2018 Certified by TUV*

---

### **Assignment No 1: Merge Sort**

**Name:** Harshit Pandita  
**PRN:** 124B1F017  
**Subject:** Design and Analysis of Algorithms  
**Batch:** A1  

---

### 1. Topic:
Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer orders based on their timestamps. The solution should handle a large dataset (up to 1 million orders) with minimal computational overhead. Additionally, analyze the time complexity and compare it with traditional sorting techniques.

### 2. Course Objective:
- To know the basics of computational complexity of various algorithms.
- To select appropriate algorithm design strategies to solve real-world problems.

### 3. Course Outcome:
- Analyze the asymptotic performance of algorithms.
- Solve computational problems by applying suitable paradigms of Divide and Conquer or Greedy methodologies.

### 4. Theory:
Merge sort is a popular sorting algorithm known for its efficiency and stability. It follows the divide and conquer approach. It works by recursively dividing the input array into two halves, recursively sorting the two halves, and finally merging them back together to obtain the sorted array.

#### Working of Merge Sort:
- **Divide:** Keep dividing the list or array into two equal halves again and again, until each part has only one element left.
- **Conquer:** Each subarray is sorted individually using the merge sort algorithm.
- **Merge:** The sorted subarrays are merged back together in sorted order. The process continues until all elements from both subarrays have been merged.

#### Complexity Analysis of Merge Sort:
- **Divide step:** The array is recursively divided into two halves until each subarray has one element. Number of times we can divide an array of size $n = \log_2(n)$ (height of recursion tree).
- **Merge step:** At each level of recursion, all $n$ elements are merged.
- **Total work** = $\text{number of levels} \times \text{work per level} = \log_2(n) \times n = O(n \log n)$.

#### Time Complexity:
- **Best Case Time Complexity:** Even if the array is already sorted, Merge Sort still divides and merges every element. Merging sorted subarrays still requires scanning through all elements.  
  $$\text{Best Case} = O(n \log n)$$
- **Average Case Time Complexity:** For randomly arranged data, the algorithm still divides into halves and merges them. On average, the number of comparisons during merging is proportional to $n$.  
  $$\text{Average Case} = O(n \log n)$$
- **Worst Case Complexity:** Even if the array is sorted in descending order (worst arrangement for comparisons), Merge Sort still performs the same divide-and-merge procedure. Comparisons may be maximum, but still bounded by $O(n \log n)$.  
  $$\text{Worst Case} = O(n \log n)$$

#### Analysis of Merge Sort Space Complexity:
In merge sort, all elements are copied into an auxiliary array of size $N$, where $N$ is the number of elements present in the unsorted array. Hence, the space complexity for Merge Sort is $O(N)$.

---

### Merge Sort Algorithm & Pseudocode

#### Merge Sort Algorithm
- **Step 1:** If it is only one element in the list, consider it already sorted, so return.
- **Step 2:** Divide the list recursively into two halves until it can no longer be divided.
- **Step 3:** Merge the smaller lists into a new list in sorted order.

#### Pseudo code
```text
ALGORITHM MergeSort(A, low, high)
1. if low >= high then
2.     return
3. end if
4. mid <- (low + high) / 2
5. MergeSort(A, low, mid)
6. MergeSort(A, mid + 1, high)
7. Merge(A, low, mid, high)
END ALGORITHM

ALGORITHM Merge(A, low, mid, high)
1. Create an empty array TEMP
2. i <- low
3. j <- mid + 1
4. while i <= mid AND j <= high do
5.     if A[i] <= A[j] then
6.         Add A[i] to TEMP
7.         i <- i + 1
8.     else
9.         Add A[j] to TEMP
10.        j <- j + 1
11.    end if
12. end while
13. while i <= mid do
14.     Add A[i] to TEMP
15.     i <- i + 1
16. end while
17. while j <= high do
18.     Add A[j] to TEMP
19.     j <- j + 1
20. end while
21. Copy all elements of TEMP back into A[low...high]
END ALGORITHM
```

---

### 5. Flow Diagram:
```text
                     +-----------------------+
                     |         Start         |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Input array of order  |
                     |timestamps (e.g. 12:30)|
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Array has >1 element? |
                     +-----+-----------+-----+
                           |           |
                      Yes  |           | No
                           v           v
            +--------------+-------+ +-+--------------------+
            | Divide array into 2  | | Return array         |
            |       halves         | | (Already sorted)     |
            +--------------+-------+ +----------------------+
                           |
            +--------------v-------+
            | Recursively call     |
            | MergeSort function   |
            +--------------+-------+
                           |
            +--------------v-------+
            |  Merge sorted halves |
            |      into TEMP       |
            +--------------+-------+
                           |
            +--------------v-------+
            | Output sorted order  |
            | timestamps           |
            +--------------+-------+
                           |
                     +-----v-----+
                     |    End    |
                     +-----------+
```

---

### 6. Example:
Customer order timestamps:  
`[12:30, 09:15, 14:45, 10:00]`

#### Step 1: Divide
- Split into halves $\rightarrow$ `[12:30, 09:15]` and `[14:45, 10:00]`
- Further split $\rightarrow$ `[12:30]`, `[09:15]`, `[14:45]`, `[10:00]`

#### Step 2: Merge & Sort
- Merge `[12:30]` and `[09:15]` $\rightarrow$ `[09:15, 12:30]`
- Merge `[14:45]` and `[10:00]` $\rightarrow$ `[10:00, 14:45]`
- Merge final two halves $\rightarrow$ `[09:15, 10:00, 12:30, 14:45]`

---

### 7. Output:
```text
Orders sorted by timestamp -> [09:15, 10:00, 12:30, 14:45]
```

---

### 8. GitHub Repository:
[https://github.com/harshitpandita/DAA-ASSIGNMENTS-124B1F017-HARSHIT-PANDITA.git](https://github.com/harshitpandita/DAA-ASSIGNMENTS-124B1F017-HARSHIT-PANDITA.git)

---

### 9. Conclusion:
Merge Sort is a highly efficient and stable sorting algorithm that organizes customer orders based on their timestamps with $O(n \log n)$ complexity. Compared to traditional algorithms like Bubble Sort or Insertion Sort, which are too slow for large inputs, Merge Sort can easily handle up to 1 million records without performance issues. Its ability to maintain the correct order and scalability makes it an excellent choice for real-world applications such as e-commerce, order tracking, and scheduling systems.
