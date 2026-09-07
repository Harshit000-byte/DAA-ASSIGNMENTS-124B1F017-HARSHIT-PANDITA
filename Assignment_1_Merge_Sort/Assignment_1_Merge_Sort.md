# Pimpri-Chinchwad Education Trust's
## Pimpri-Chinchwad College of Engineering
*(An Autonomous Institute)*  
*Affiliated to Savitribai Phule Pune University (SPPU) | ISO 21001:2018 Certified by TUV*

---

### **Assignment No. 1**
### **Merge Sort**

**Name:** Harshit Pandita  
**PRN:** 124B1F017  
**Subject:** Design and Analysis of Algorithms  
**Batch:** A1  

---

### 1. Problem Statement:
Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer orders based on their timestamps. The solution should handle a large dataset (up to 1 million orders) with minimal computational overhead. Additionally, analyze the time complexity and compare it with traditional sorting techniques.

### 2. Course Objective:
2.1. To know the basics of computational complexity of various algorithms.  
2.2. To select appropriate algorithm design strategies to solve real-world problems.  

### 3. Course Outcome:
3.1. Analyze the asymptotic performance of algorithms  
3.2. Solve computational problems by applying suitable paradigms of Divide and Conquer or Greedy methodologies  

---

### Theory:
Merge sort is a popular sorting algorithm known for its efficiency and stability. It follows the divide and conquer approach. It works by recursively dividing the input array into two halves, recursively sorting the two halves and finally merging them back together to obtain the sorted array.

#### Working of Merge Sort:
- **Divide:** Keep dividing the list or array into two equal halves again and again, until each part has only one element left.
- **Conquer:** Each sub array is sorted individually using the merge sort algorithm.
- **Merge:** The sorted sub arrays are merged back together in sorted order. The process continues until all elements from both sub arrays have been merged.

#### Complexity Analysis of Merge Sort:
- **Divide step:** The array is recursively divided into two halves until each subarray has one element. Number of times we can divide an array of size $n = \log_2(n)$ (height of recursion tree).
- **Merge step:** At each level of recursion, all $n$ elements are merged.
- **Total work** = number of levels $\times$ work per level $= \log_2(n) \times n = O(n \log n)$.

#### Analysis of Merge Sort Time Complexity:

##### Best Case Time Complexity
Even if the array is already sorted, Merge Sort still **divides** and **merges** every element. Merging sorted sub arrays still requires scanning through all elements.  
$$\text{Best Case} = O(n \log n)$$

##### Average Case Time Complexity
- For randomly arranged data, the algorithm still divides into halves and merges them.
- On average, the number of comparisons during merging is proportional to $n$.  
$$\text{Average Case} = O(n \log n)$$

##### Worst Case Complexity
- Even if the array is sorted in **descending order** (worst arrangement for comparisons), Merge Sort still performs the same divide-and-merge procedure.
- Comparisons may be maximum, but still bounded by $O(n \log n)$.  
$$\text{Worst Case} = O(n \log n)$$

#### Analysis of Merge Sort Space Complexity:
In merge sort, all elements are copied into an **auxiliary array** of size $N$, where $N$ is the number of elements present in the unsorted array. Hence, the space complexity for **Merge Sort** is $O(N)$.

---

### Merge Sort Algorithm
- **Step 1:** If it is only one element in the list, consider it already sorted, so return.
- **Step 2:** Divide the list recursively into two halves until it can’t no more be divided.
- **Step 3:** Merge the smaller lists into new list in sorted order.

### Pseudo code
```text
procedure mergesort( var a as array )
if ( n == 1 ) return a
    var l1 as array = a[0] ... a[n/2]
    var l2 as array = a[n/2+1] ... a[n]
    l1 = mergesort( l1 )
    l2 = mergesort( l2 )
    return merge( l1, l2 )
end procedure

procedure merge( var a as array, var b as array )
    var c as array
    while ( a and b have elements )
        if ( a[0] > b[0] )
            add b[0] to the end of c
            remove b[0] from b
        else
            add a[0] to the end of c
            remove a[0] from a
        end if
    end while
    while ( a has elements )
        add a[0] to the end of c
        remove a[0] from a
    end while
    while ( b has elements )
        add b[0] to the end of c
        remove b[0] from b
    end while
    return c
end procedure
```

---

### 5. Flow Diagram:
```text
                     +-----------------------+
                     |         START         |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Input Array of        |
                     | Customer Orders       |
                     | (With Timestamps)     |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Array has 1 element?  |
                     +-----+-----------+-----+
                           |           |
                      Yes  |           | No
                           v           v
            +--------------+-------+ +-+--------------------+
            | Return Array         | | Divide Array in 2    |
            | (Already Sorted)     | | Halves               |
            +----------------------+ +---------+------------+
                                               |
                                     +---------v------------+
                                     | Recursively Call     |
                                     | Merge Sort Function  |
                                     +---------+------------+
                                               |
                                     +---------v------------+
                                     | Is Left[i] <=        |
                                     | Right[j]?            |
                                     +----+------------+----+
                                          |            |
                                     Yes  v            v  No
                            +-------------+---+    +---+--------------+
                            | Copy Left[i] to |    | Copy Right[j] to |
                            | Result Array    |    | Result Array     |
                            +-------------+---+    +---+--------------+
                                          |            |
                                          +-----+------+
                                                |
                                     +----------v-----------+
                                     | Repeat until all     |
                                     | elements merged      |
                                     +----------+-----------+
                                                |
                                     +----------v-----------+
                                     | Output Sorted        |
                                     | Customer Orders      |
                                     +----------+-----------+
                                                |
                                     +----------v-----------+
                                     |          END         |
                                     +----------------------+
```

---

### 6. Example:
Customer order timestamps:  
`[12:30, 09:15, 14:45, 10:00]`

#### Step 1: Divide
- Split into halves $\rightarrow [12:30, 09:15]$ and $[14:45, 10:00]$
- Further split $\rightarrow [12:30], [09:15], [14:45], [10:00]$

#### Step 2: Merge & Sort
- Merge $[12:30]$ and $[09:15] \rightarrow [09:15, 12:30]$
- Merge $[14:45]$ and $[10:00] \rightarrow [10:00, 14:45]$
- Merge final two halves $\rightarrow [09:15, 10:00, 12:30, 14:45]$

---

### Output:
Orders sorted by timestamp $\rightarrow$ `[09:15, 10:00, 12:30, 14:45]`

---

### Conclusion:
Merge Sort is a highly efficient and stable sorting algorithm that organizes customer orders based on their timestamps with **$O(n \log n)$** complexity. Compared to traditional algorithms like Bubble Sort or Insertion Sort, which are too slow for large inputs, Merge Sort can easily handle up to **1 million records** without performance issues. Its ability to maintain the correct order and scalability makes it an excellent choice for real-world applications such as **e-commerce, order tracking, and scheduling systems**.

---

### GitHub Repository:
https://github.com/Harshit000-byte/DAA-ASSIGNMENTS-124B1F017-HARSHIT-PANDITA.git
