#pragma once
#include <vector>
#include <chrono>

namespace InsertionTimed {

    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::nanoseconds;

    inline Duration sort(std::vector<int>& arr, int low = 0, int high = -1) {
        if (high == -1) high = arr.size() - 1;

        auto start = Clock::now();

        for (int i = low + 1; i <= high; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }

        auto end = Clock::now();
        return std::chrono::duration_cast<Duration>(end - start);
    }

}
