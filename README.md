Data Structures Used
1. unordered_map<uint64_t, new_order> order_map

Purpose:

Stores all active orders indexed by order_id

Why used:

Provides O(1) average lookup for:
Change order
Cancel order

Without this, we would need O(n) search.

2. map<int32_t, uint64_t, greater<int32_t>> buys

Purpose:

Stores aggregated buy-side volume per price

Why map:

Maintains sorted order automatically
Using greater<> ensures:
Highest price first (required for bids)
3. map<int32_t, uint64_t> sells

Purpose:

Stores aggregated sell-side volume per price

Why map:

Maintains ascending order
Lowest price first (required for asks)
Function Implementations
1. OnNewOrder

Logic:

Insert order into order_map
Add quantity to corresponding price level in:
buys if side = 'B'
sells if side = 'S'

Time Complexity:

unordered_map insert → O(1) average
map insert/update → O(log N)

Overall: O(log N)

2. OnChangeOrder

Logic:

Lookup order using order_id
Remove old quantity from its price level
Update price and quantity
Add new quantity to updated price level

Key Idea:

Change operation = remove old state + insert new state

Time Complexity:

Lookup → O(1)
Removal from map → O(log N)
Insertion into map → O(log N)

Overall: O(log N)

3. OnCancelOrder

Logic:

Lookup order
Subtract its quantity from the price level
Remove price level if quantity becomes zero
Erase order from order_map

Time Complexity:

Lookup → O(1)
Map update → O(log N)

Overall: O(log N)

4. Print

Logic:

Iterate over:
buys (already sorted descending)
sells (already sorted ascending)

Time Complexity:

O(N) where N = number of price levels
