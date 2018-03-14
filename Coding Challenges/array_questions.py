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
    def find_min_2(list_: List) -> int:
        return list_.index(min(list_))

    @staticmethod
    def find_contiguous_sum(list_: List) -> int:
        max_till_now, max_int = list_[0], list_[0]
        for item in list_:
            max_till_now = max_till_now + item if max_till_now + item > item else item
            max_int = max_till_now if max_till_now > max_int else max_int
        return max_int

    @staticmethod
    def remove_duplicates(list_: List) -> List[int]:
        buff = {}
        for i in range(len(list_)):
            if list_[i] in buff:
                list_.remove(list_[i])
            else:
                buff[list_[i]] = i
        return list_
    
    @staticmethod
    def remove_duplicates_2(arr: List) -> List[int]:
        return list(set(arr))


if __name__ == "__main__":
    arr = [2, -3, 4, -5, 3, 4]
    min_val = Solution.find_min(arr)
    max_sum = Solution.find_contiguous_sum(arr)
    list_no_duplicates = Solution.remove_duplicates(arr)
    print(min_val)
    print(max_sum)
    print(list_no_duplicates)
