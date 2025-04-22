Anthony Chandra


Part I - Binary Search
Time Complexity: O(log n)
Explanation:
Binary search works by repeatedly dividing the search interval in half. After each comparison, the size of the search space is reduced by half. 

Each step reduces the search space by half or divide by 2 and so the maximum number of steps needed is log_2(n)
Therefore, the time complexity is O(log n)

Binary search is significantly more efficient than linear search (O(n)) for when larger sorted datasets come into play.

Part II - Sorting Algorithms
1. Bubble Sort
Time Complexity:
O(n²)

Explanation:
Bubble Sort works by repeatedly going through the whole list, comparing the elements that are beside each other, and swapping them if they are in the wrong order. 

We need to make n-1 passes through the array, and in each pass, we make up to n-1 comparisons. This gives us (n-1) × (n-1) operations, which simplifies to O(n²).

2. Merge Sort
Time Complexity:
O(n log n)

Explanation:
Merge Sort is a divide-and-conquer algorithm that divides the input array into two halves, recursively sorts both halves and then merges the sorted halves.

Dividing the array takes constant time, the algorithm then divides the array log n times and each level of division requires n operations to merge the subarrays back so the total time complexity is O(n log n).

3. Quick Sort
Time Complexity:
O(n log n)

Explanation:
Quick Sort is another divide-and-conquer algorithm that selects a pivot element, in my case I picked the high or right, partitions the array around the pivot and then recursively sorts the partitions.

The pivot divides the array into roughly equal halves, giving a time complexity of O(n log n).

Part III - Tower of Hanoi
Time Complexity: O(2^n)
Explanation:
The Tower of Hanoi is solved recursively by
First, moving (n-1) disks from source to auxiliary rod then moving the nth disk from source to destination rod and last moving (n-1) disks from auxiliary to destination rod repeatedly.

The recurrence relation for the number of moves is:
T(1) = 1 (base case)
T(n) = 2T(n-1) + 1 (for n > 1)

This gives an exponential time complexity of O(2^n) and explains why the number of moves grows exponentially:

1 disk: 1 move

2 disks: 3 moves

3 disks: 7 moves

4 disks: 15 moves
