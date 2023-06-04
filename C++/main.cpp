#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// 快速排序的分區函數（Hoare partition scheme）.
int partition(std::vector<int>& nums, int low, int high) {
    int pivot = nums[low + (high - low) / 2];  // 選擇中間的元素作為基準點.
    int i = low - 1;  // 初始化左指標.
    int j = high + 1;  // 初始化右指標.

    while (true) {
        do {
            i++;
        } while (nums[i] < pivot);

        do {
            j--;
        } while (nums[j] > pivot);

        if (i >= j) {
            return j;  // 返回右指標.
        }

        std::swap(nums[i], nums[j]);
    }
}

// 堆排序.
void heapSort(std::vector<int>& nums) {
    std::make_heap(nums.begin(), nums.end());
    std::sort_heap(nums.begin(), nums.end());
}

// 內省式快速排序.
void introsort(std::vector<int>& nums, int low, int high, int depthLimit) {
    const int sizeThreshold = 16;  // 用於切換到堆排序的閾值.

    if (high - low > sizeThreshold) {
        if (depthLimit == 0) {
            // 遞迴深度達到閾值，切換到堆排序.
            heapSort(nums);
            return;
        }

        int pivotIndex = partition(nums, low, high);
        introsort(nums, low, pivotIndex, depthLimit - 1);
        introsort(nums, pivotIndex + 1, high, depthLimit - 1);
    } else {
        // 小型數列使用插入排序.
        std::sort(nums.begin() + low, nums.begin() + high + 1);
    }
}

int main() {
    std::vector<int> nums = {50, 90, 70, 20, 10, 30, 40, 60, 80};

    // 原始數列.
    std::cout << "Original array: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 內省式快速排序.
    int depthLimit = 2 * static_cast<int>(std::log2(nums.size()));
    introsort(nums, 0, nums.size() - 1, depthLimit);

    // 排序後數列.
    std::cout << "Sorted array: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
