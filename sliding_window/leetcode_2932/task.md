You are given a 0-indexed integer array nums. A pair of indices i, j is called a strong pair if |nums[i] - nums[j]| <= min(nums[i], nums[j]).

Return the maximum possible value of nums[i] XOR nums[j] among all strong pairs in nums, or 0 if no strong pair exists.

Example 1:

Input: nums = [1,2,3,4,5]
Output: 7
Explanation: The strong pairs are: (1,2), (1,3), (2,3), (2,4), (3,4), (3,5), (4,5). The maximum XOR is from (3,5): 3 XOR 5 = 7.

Example 2:

Input: nums = [10,100]
Output: 0
Explanation: No strong pair exists.

Example 3:

Input: nums = [500,520,2500,3000]
Output: 1020
Explanation: The maximum XOR is from (500, 520): 500 XOR 520 = 1020.

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 2^20 - 1
