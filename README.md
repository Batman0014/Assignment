# Implementation (C++)

## Data Structures Used

### 1. unordered_map<uint64_t, new_order> order_map
- Stores all active orders indexed by `order_id`

### 2. map<int32_t, uint64_t, greater<int32_t>> buys
- Stores aggregated buy-side quantity per price
- Sorted in descending order (highest price first)

### 3. map<int32_t, uint64_t> sells
- Stores aggregated sell-side quantity per price
- Sorted in ascending order (lowest price first)
  

## Function Implementations

### OnNewOrder
- Inserts order into `order_map`
- Adds quantity to corresponding price level

**Time Complexity:**
- unordered_map insert → O(1) average
- map update → O(log N)

**Overall:** O(log N)

---

### OnChangeOrder
- Finds order using `order_id`
- Removes old quantity from its price level
- Updates price and quantity
- Adds new quantity to updated price level

**Key Idea:**
Change = remove old state + insert new state

**Time Complexity:**
- Lookup → O(1)
- Map updates → O(log N)

**Overall:** O(log N)

---

### OnCancelOrder
- Finds order using `order_id`
- Removes its quantity from price level
- Deletes order from `order_map`

**Time Complexity:**
- Lookup → O(1)
- Map update → O(log N)

**Overall:** O(log N)

---

### Print
- Iterates over buy and sell maps
- Displays aggregated quantities

**Time Complexity:**
- O(N), where N = number of price levels

---


## Complexity Summary

| Operation        | Complexity |
|-----------------|------------|
| New Order       | O(log N)   |
| Change Order    | O(log N)   |
| Cancel Order    | O(log N)   |
| Lookup (ID)     | O(1)       |
| Print           | O(N)       |

---

