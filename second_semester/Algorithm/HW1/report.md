# Hybrid Sorting Performance Analysis Report (QuickSort / MergeSort with InsertionSort)

## Terminal Condition and Hybrid Design
### In this experiment, I implemented both QuickSort and MergeSort with a hybrid strategy:
when the input size of a subproblem becomes smaller than or equal to a threshold (I chose 40 for QuickSort 600 for MergeSort), the algorithm switches from recursive sorting to InsertionSort.

This technique is commonly used in practice because although InsertionSort has a worse time complexity in theory (O(n²)), it performs faster on small datasets due to:
	•	Low constant overhead
	•	Better cache locality
	•	No recursion cost

## Experimental Setup
### I tested both hybrid sorting algorithms using the following input sizes:
• Small inputs: n = 2 to 40 (for QuickSort vs. InsertionSort)
• Large inputs: n = 480 to 600 (for MergeSort vs. InsertionSort)

Each test case generates a fresh random input of size n and measures the execution time of both the hybrid sort and standalone InsertionSort using std::chrono.

## Code Structure
##### To organize and test each sorting algorithm effectively, I separated the implementation into multiple source files and classes:

### main.cpp

This file handles the experiment execution. It defines a list of input sizes, generates random arrays, and runs hybrid QuickSort and MergeSort on each. It prints the timing results for each test case.

### quick_sort.hpp & quick_sort.cpp

These implement the Quick class, which performs QuickSort with a hybrid strategy:
	•	Uses InsertionSort when the subarray size is below a set threshold (e.g., 40)
	•	Measures the time for both hybrid QuickSort and standalone InsertionSort
	•	Keeps two copies of the array for fair comparison

### merge_sort.hpp & merge_sort.cpp

These implement the Merge class, which handles hybrid MergeSort:
	•	Also uses InsertionSort as a base case
	•	Performs standard merge operation
	•	Tracks execution time for both algorithms

### insertion_sort.hpp

Defines the InsertionTimed::sort() function:
	•	Performs InsertionSort
	•	Returns execution time using std::chrono

#### This modular structure allows isolated testing of each algorithm under the same conditions.

## Observations

### QuickSort vs InsertionSort (n = 2 to 40):

• For very small sizes (n ≤ 10), InsertionSort performs faster or equally compared to QuickSort.
• Around n = 30~40, QuickSort begins to outperform InsertionSort, and the performance gap widens as n increases.
• By n = 40, QuickSort becomes consistently faster than InsertionSort, justifying the decision to switch sorting strategy above this threshold.

### MergeSort vs InsertionSort (n = 480 to 600):

• InsertionSort’s performance deteriorates quickly due to its quadratic time complexity.
• MergeSort, although more complex, scales well with increasing input size, showing substantially better performance starting from n ≈ 500.
• At n = 600, the time difference becomes significantly large, clearly favoring MergeSort for large inputs.

![截圖 2025-04-13 晚上11.11.46](https://hackmd.io/_uploads/H1jmRIFC1x.png)

#### As shown in the time measurements, this hybrid approach significantly improves sorting efficiency across different input sizes.

### To evaluate the effectiveness of the hybrid sorting strategy, I implemented two test functions:
```
void QuickSort_with_InsertionSort(std::vector<int> &inputSizes);
void MergeSort_with_InsertionSort(std::vector<int> &inputSizes);
```

These functions iterate through a list of different input sizes and perform the following steps:
	1.	Generate a random array of size n using generate_random_array(n).
	2.	Run the hybrid sort (QuickSort or MergeSort with a terminal condition that switches to InsertionSort).
	3.	Run standalone InsertionSort on a copy of the same data.
	4.	Measure execution time for both algorithms using std::chrono::high_resolution_clock.
	5.	Print the time results to compare the performance.

#### QuickSort_with_InsertionSort Example:
```
void QuickSort_with_InsertionSort(std::vector<int> &inputSizes) {
  for (int n : inputSizes) {
    std::chrono::nanoseconds total_quick{0}, total_insert{0};
    std::vector<int> sample = generate_random_array(n);
    Quick sorter(sample);
    std::chrono::nanoseconds Quick = sorter.quick_duration();
    std::chrono::nanoseconds Insertion = sorter.insertion_duration();

    std::cout << "n = " << std::setw(7) << n << " | ";
    std::cout << "QuickSort " << Quick.count() << " ns, ";
    std::cout << "InsertionSort " << Insertion.count() << " ns\n";
  }
}
```
•	A new Quick object is constructed with the sample array.
•	Internally, Quick sorts one copy using hybrid QuickSort and another using InsertionSort.
•	The result is printed for comparison.

####  MergeSort_with_InsertionSort Example:
```
void MergeSort_with_InsertionSort(std::vector<int> &inputSizes) {
  for (int n : inputSizes) { 
    std::chrono::nanoseconds total_quick{0}, total_insert{0};
    std::vector<int> sample = generate_random_array(n);
    Merge sorter(sample);
    std::chrono::nanoseconds Merge = sorter.merge_duration();
    std::chrono::nanoseconds Insertion = sorter.insertion_duration();

    std::cout << "n = " << std::setw(7) << n << " | ";
    std::cout << "MergeSort " << Merge.count() << " ns, ";
    std::cout << "InsertionSort " << Insertion.count() << " ns\n";
  }
}
```
This function is almost identical in structure to the QuickSort version, but it uses a Merge object to test the hybrid MergeSort.

###  Internal Class Structure for Timing
Both Quick and Merge are classes designed to:
	•	Store two copies of the input array (array1 and array2)
	•	Sort one with the hybrid sort
	•	Sort the other with InsertionSort
	•	Record the time taken for both

####  Quick Constructor:
```
Quick::Quick(std::vector<int> &a) {
  this->array1.assign(a.begin(), a.end());
  this->array2.assign(a.begin(), a.end());

  this->start_quick = high_resolution_clock::now();
  quickSort(array1, 0, a.size() - 1);
  this->end_quick = high_resolution_clock::now();

  this->insertion_time = InsertionTimed::sort(array2, 0, array2.size());
}
```
•	array1: used for hybrid QuickSort
•	array2: used for InsertionSort
•	The duration of QuickSort is calculated from start_quick to end_quick
•	The insertion sort timing is directly returned by InsertionTimed::sort()

#### Merge Constructor:
```
Merge::Merge(std::vector<int> &a) {
  this->array1.assign(a.begin(), a.end());
  this->array2.assign(a.begin(), a.end());

  this->start_merge = high_resolution_clock::now();
  merge_sort(this->array1);
  this->end_merge = high_resolution_clock::now();

  this->insertion_time = InsertionTimed::sort(array2, 0, array2.size());
}
```
Similar to Quick, but runs merge_sort() on array1 for hybrid MergeSort.
 
### Performance Conclusion

![截圖 2025-04-14 凌晨12.22.08](https://hackmd.io/_uploads/Syf6EPYCJg.png)

The results show that both QuickSort and MergeSort scale well with increasing input sizes, and both benefit from the hybrid strategy using InsertionSort for small subarrays.

However, some performance differences were observed:
	•	For smaller inputs (e.g., n = 100):
QuickSort slightly outperforms MergeSort (8125 ns vs 11,458 ns), likely due to lower overhead and more efficient in-place partitioning.
	•	For medium to large inputs (e.g., n = 10,000 to 100,000):
QuickSort consistently performs faster than MergeSort.
For example, at n = 100,000, QuickSort finishes in approximately 16 ms, while MergeSort takes over 54 ms.

This suggests that the hybrid QuickSort implementation is better optimized for speed in this context, particularly due to fewer memory allocations. In contrast, MergeSort requires extra memory during the merge step, which introduces overhead.

The increasing time remains roughly logarithmic for QuickSort and slightly steeper for MergeSort, which aligns with their expected theoretical complexities of O(n log n).

### Conclusion

Although the raw timing values may fluctuate depending on system load, the overall trend clearly demonstrates the effectiveness of hybrid sorting techniques. It also highlights how implementation details and memory usage patterns can significantly influence real-world performance — even between algorithms with the same theoretical complexity.

Furthermore, for larger inputs such as n = 1,000,000, the unoptimized MergeSort implementation exhibits substantial slowdowns due to repeated memory copying and allocation during merging. This gap suggests that MergeSort can benefit greatly from optimization techniques such as shared buffers or in-place merge operations. Despite this, the test at n = 1,000,000 was retained to fulfill the experiment’s completeness and better illustrate the performance impact of implementation design.

