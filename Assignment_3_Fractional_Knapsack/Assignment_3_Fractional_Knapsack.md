# Pimpri-Chinchwad Education Trust's
## Pimpri-Chinchwad College of Engineering
*(An Autonomous Institute)*  
*Affiliated to Savitribai Phule Pune University (SPPU) | ISO 21001:2018 Certified by TUV*

---

### **Assignment No 3: Fractional Knapsack Emergency Relief Supply Distribution**

**Name:** Harshit Pandita  
**PRN:** 124B1F017  
**Subject:** Design and Analysis of Algorithms  
**Batch:** A1  

---

### 1. Problem Statement:
A devastating flood has hit multiple villages in a remote area, and the government, along with NGOs, is organizing an emergency relief operation. A rescue team has a limited-capacity boat that can carry a maximum weight of $W$ kilograms. The boat must transport critical supplies, including food, medicine, and drinking water, from a relief center to the affected villages.

Each type of relief item has:
- A weight ($w_i$) in kilograms.
- Utility value ($v_i$) indicating its importance (e.g., medicine has higher value than food).
- Some items can be divided into smaller portions (e.g., food and water), while others must be taken as a whole (e.g., medical kits).

### 2. Goals:
1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the supplies transported.
2. Prioritize high-value items while considering weight constraints.
3. Allow partial selection of divisible items (e.g., carrying a fraction of food packets).
4. Ensure that the boat carries the most critical supplies given its weight limit $W$.

### 3. Course Objectives:
- To know the basics of computational complexity of various algorithms.
- To select appropriate algorithm design strategies to solve real-world problems.

### 4. Course Outcomes:
After learning the course, students will be able to:
- Analyze the asymptotic performance of algorithms.
- Solve computational problems by applying suitable paradigms such as Greedy method.

### 5. Theory:
The Fractional Knapsack Problem is a classic optimization problem: given a set of items—each with weight $w_i$ and value $v_i$—and a maximum capacity $W$, the objective is to maximize total value by selecting items (or fractions of them) up to capacity.

Unlike the 0/1 Knapsack, the fractional version allows partial selection, making it solvable optimally in polynomial time.

#### Algorithm (Greedy Strategy):
1. Compute the value-to-weight ratio $v_i / w_i$ for each item.
2. Sort items in **descending order** of this ratio.
3. Fill the knapsack:
   - Take items fully if they fit.
   - If capacity runs out, take the exact fraction needed of the current item (only if divisible).
   - Skip indivisible items that do not fit.

#### Working of Greedy:
1. **Greedy-choice property:** Choosing the highest ratio item at each step is always part of an optimal solution.
2. **Optimal substructure:** Once part of the knapsack is filled, the remaining capacity forms a smaller instance of the same problem.

---

### 6. Time and Space Complexity:
- **Ratio computation:** $O(n)$
- **Sorting:** $O(n \log n)$
- **Selection:** $O(n)$
- **Total Time Complexity:** $O(n \log n)$

---

### 7. Pseudo code:
```text
ALGORITHM MaxUtilFractional(items, W)
Input:
    items = list of (weight w, value v, isDivisible)
    W = maximum capacity
Output:
    Maximum total utility value

1. for each item in items do
2.     ratio <- value / weight
3. end for
4. Sort items in descending order of ratio
5. totalValue <- 0
6. remainingCapacity <- W
7. for each item in sorted items do
8.     if remainingCapacity = 0 then
9.         break
10.    end if
11.    if item.weight <= remainingCapacity then
12.        totalValue <- totalValue + item.value
13.        remainingCapacity <- remainingCapacity - item.weight
14.    else if item.isDivisible = true then
15.        fraction <- remainingCapacity / item.weight
16.        totalValue <- totalValue + (fraction * item.value)
17.        remainingCapacity <- 0
18.    else
19.        // Item is indivisible and cannot fit
20.        continue
21.    end if
22. end for
23. return totalValue
END ALGORITHM
```

---

### 8. Flow Diagram:
```text
                     +-----------------------+
                     |         Start         |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Input: n items with   |
                     | weights, values, W    |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Compute value-weight  |
                     | ratio for each item   |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | Sort items in desc.   |
                     | order of ratio        |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
                     | i=0, TotalValue=0,    |
                     | RemainingCapacity = W |
                     +-----------+-----------+
                                 |
                     +-----------v-----------+
             +-------> RemainingCapacity > 0 |
             |       |       and i < n?      |
             |       +-----+-----------+-----+
             |             |           |
             |        Yes  |           | No
             |             v           |
             |       +-----+-----+     |
             |       |Weight[i] <=|    |
             |       | Remaining?|     |
             |       +--+-----+--+     |
             |          |     |        |
             |     Yes  |     | No     v
             |          |     +----+ +-+--------------------+
             |          v          | | Output TotalValue    |
             |  +-------+-------+  v +----------+-----------+
             |  | Take full item|  |            |
             |  | Update rem.   |  v            v
             |  | capacity      | +-------------+----------+
             |  +-------+-------+ | Take fraction of item  |
             |          |         | Update TotalValue      |
             |          |         | RemainingCapacity = 0  |
             |          |         +-------------+----------+
             |          |                       |
             +----------+-----------------------+
                                                |
                                          +-----v-----+
                                          |    End    |
                                          +-----------+
```

---

### 9. Example:

| Item | Weight ($kg$) | Utility | Divisible | Taken | Value Obtained |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Medicine** | 5 | 50 | No | Full | 50 |
| **Food** | 10 | 30 | Yes | Full | 30 |
| **Water** | 20 | 20 | Yes | Partial (if needed) | up to 20 |

**Maximum Utility = 100** (if all fit in given $W$).  
**Boat capacity:** $17\text{ kg}$

#### Step 1: Calculate utility per kg
- **Medicine:** $50 / 5 = 10$
- **Food:** $30 / 10 = 3$
- **Water:** $20 / 20 = 1$

$$\text{Preference order: Medicine} \rightarrow \text{Food} \rightarrow \text{Water}$$

#### Step 2: Fill the boat
- **Take Medicine fully:**
  - Weight used = $5\text{ kg}$
  - Utility = $50$
  - Remaining capacity = $17 - 5 = 12\text{ kg}$
- **Take Food fully** (weight $10\text{ kg}$, divisible):
  - Fits completely
  - Utility = $30$
  - Remaining capacity = $12 - 10 = 2\text{ kg}$
- **Take Water partially** (weight $20\text{ kg}$, divisible):
  - Only $2\text{ kg}$ fits
  - Utility = $20 \times (2 / 20) = 2$

#### Step 3: Total Utility
- Medicine: 50
- Food: 30
- Water (partial): 2

$$\mathbf{Total\ Utility = 82}$$

---

### 10. GitHub Repository:
[https://github.com/harshitpandita/DAA-ASSIGNMENTS-124B1F017-HARSHIT-PANDITA.git](https://github.com/harshitpandita/DAA-ASSIGNMENTS-124B1F017-HARSHIT-PANDITA.git)

---

### 11. Conclusion:
The **Fractional Knapsack Algorithm** maximizes utility by prioritizing items with the highest value-to-weight ratio. In emergency relief logistics, this ensures that life-saving items like medicine kits are transported first, followed by food and water as space allows. The greedy algorithm is both efficient ($O(n \log n)$) and optimal for fractional cases, making it highly effective in disaster management where quick, resource-optimized decisions are critical.
