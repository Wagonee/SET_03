#ifndef A2I__ARRAYGENERATOR_H_
#define A2I__ARRAYGENERATOR_H_

#include <random>
#include <vector>
#include <algorithm>

class ArrayGenerator {
 public:
  static std::vector<int> GenerateArr(int left_border, int right_border, size_t size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(left_border, right_border);
    for (size_t i = 0; i < size; ++i) {
      arr[i] = dis(gen);
    }
    return arr;
  }

  static std::vector<int> GenerateReverseArr(int left_border, int right_border, size_t size) {
    std::vector<int> arr = GenerateArr(left_border, right_border, size);
    std::sort(arr.begin(), arr.end(), std::greater<>());
    return arr;
  }

  static std::vector<int> GenerateAlmostSortedArr(int left_border, int right_border, size_t size) {
    std::vector<int> arr = GenerateArr(left_border, right_border, size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    std::sort(arr.begin(), arr.end());
    for (size_t j = 0; j < size / 50; ++j) {
      int idx_1 = dis(gen);
      int idx_2 = dis(gen);
      std::swap(arr[idx_1], arr[idx_2]);
    }
    return arr;
  }
};

#endif //A2I__ARRAYGENERATOR_H_
