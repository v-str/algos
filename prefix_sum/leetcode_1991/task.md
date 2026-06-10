Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e., the smallest amongst all the possible ones).

A middleIndex is an index where the sum of the numbers strictly to the left of the index is equal to the sum of the numbers strictly to the right of the index.

If the index is on the left edge of the array, then the left sum is 0 (because there are no elements to the left of the index).
If the index is on the right edge of the array, then the right sum is 0.

Return the leftmost middleIndex that satisfies the condition, or -1 if there is no such index.

Example 1:

Input: nums = [2, 3, -1, 8, 4]
Output: 3
Explanation:
The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
The sum of the numbers after index 3 is: 4 = 4

Example 2:

Input: nums = [1, -1, 4]
Output: 2
Explanation:
The sum of the numbers before index 2 is: 1 + -1 = 0
The sum of the numbers after index 2 is: 0

Example 3:

Input: nums = [2, 5]
Output: -1
Explanation:
There is no middleIndex.

Constraints:

1 <= nums.length <= 100
-1000 <= nums[i] <= 1000
