#ifndef A2I__SORTTESTER_H_
#define A2I__SORTTESTER_H_

#include <vector>
#include <chrono>
#include <algorithm>

class SortTester {
  static void insertionSort(std::vector<int>& arr, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; ++i) {
      int key = arr[i];
      size_t j = i;
      while (j > left && arr[j - 1] > key) {
        arr[j] = arr[j - 1];
        --j;
      }
      arr[j] = key;
    }
  }

  static void merge(std::vector<int> &arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (size_t i = 0; i < n1; ++i) {
      L[i] = arr[left + i];
    }
    for (size_t j = 0; j < n2; ++j) {
      R[j] = arr[mid + 1 + j];
    }

    size_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        arr[k] = L[i];
        ++i;
      } else {
        arr[k] = R[j];
        ++j;
      }
      ++k;
    }

    while (i < n1) {
      arr[k] = L[i];
      ++i;
      ++k;
    }
    while (j < n2) {
      arr[k] = R[j];
      ++j;
      ++k;
    }
  }

 public:
  static void mergeSort(std::vector<int> &arr, size_t left, size_t right) {
    if (left < right) {
      size_t mid = left + (right - left) / 2;
      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);
      merge(arr, left, mid, right);
    }
  }
  static void combinedSort(std::vector<int>& arr, size_t left, size_t right, size_t threshold) {
    if (right - left + 1 <= threshold) {
      insertionSort(arr, left, right);
    } else {
      size_t mid = left + (right - left) / 2;
      combinedSort(arr, left, mid, threshold);
      combinedSort(arr, mid + 1, right, threshold);
      merge(arr, left, mid, right);
    }
  }

  static void combinedSort(std::vector<int>& arr, size_t threshold = 15) {
    if (arr.size() > 1) {
      combinedSort(arr, 0, arr.size() - 1, threshold);
    }
  }
  static size_t mergeSortTime(std::vector<int> arr, size_t repetitions) {
    size_t totalDuration = 0;

    for (size_t i = 0; i < repetitions; ++i) {
      std::vector<int> tempArr = arr;
      auto start = std::chrono::high_resolution_clock::now();
      mergeSort(tempArr, 0, tempArr.size() - 1);
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      totalDuration += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }
    return totalDuration / repetitions;
  }

  static size_t combinedSortTime(std::vector<int> arr, size_t repetitions) {
    size_t totalDuration = 0;
    for (size_t i = 0; i < repetitions; ++i) {
      std::vector<int> tempArr = arr;
      auto start = std::chrono::high_resolution_clock::now();
      combinedSort(tempArr, 15);
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      totalDuration += std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }
    return totalDuration / repetitions;
  }
};

#endif //A2I__SORTTESTER_H_
