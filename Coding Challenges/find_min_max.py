from typing import List

class Solution:
    @staticmethod
    def find_min(list_: List) -> int:
        min_index = 0
        for x in range(len(list_)):
            if(list_[x] < list_[min_index]):
                min_index = x
        return min_index

    @staticmethod
    def find_contiguous_sum(list_: List) -> int:
        max_int = -999999
        max_till_here = 0
        for i in range(len(list_)):
            max_till_here = max_till_here + list_[i]
            if(max_int < max_till_here):
                max_int = max_till_here
        return max_int


if __name__ == "__main__":
    arr = [2, -3, 4, -5, 3]
    min_val = Solution.find_min(arr)
    max_sum = Solution.find_contiguous_sum(arr)
    print(min_val)
    print(max_sum)
