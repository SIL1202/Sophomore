#include <iostream>
#include <vector>

typedef double DataType;
std::vector<DataType> given;
struct DataSet {
  size_t begin, count;
};

//
/*
void solve(DataSet input, std::vector<DataType> &Max) {
  DataType val = given[input.begin];
  if (input.count == 1) {
    Max.push_back(val);
    std::sort(Max.begin(), Max.end(),
              [](DataType a, DataType b) { return a > b; });
    if (Max.size() > 3)
      Max.pop_back();
    return;
  }

  DataSet temp[2]; // use array instead of dynamic allocate
  // std::vector<DataSet> temp(2);
  temp[0].begin = input.begin;                   // 0 ... 5 ... 10
  temp[0].count = (input.count + 1) / 2;         // (11+1) / 2 = 6
  temp[1].begin = temp[0].begin + temp[0].count; // 5  6  7    8 9
  temp[1].count = input.count / 2;               // 11 / 2 = 5

  solve(temp[0], Max);
  solve(temp[1], Max);
}

int main() {
  DataSet data;
  given = {5, 33, 3, 45, 8, 9, 2, 1, 7, 0, 55};
  data.count = given.size();
  data.begin = 0;
  std::vector<DataType> Max;
  solve(data, Max);
  for (DataType &answer : Max)
    std::cout << answer << " ";
  return 0;
}
*/
// slowest version
/*
DataType solve(DataSet input, std::vector<DataType> &Max) {
  if (input.count == 1) {
    for (int i = 0; i < Max.size(); i++) {
      if (given[input.begin] == Max[i]) {
        return 0;
      }
    }
    return given[input.begin];
  }

  DataSet temp[2];             // use array instead of dynamic allocate
                               // std::vector<DataSet> temp(2);
  temp[0].begin = input.begin; // 0 ... 5 ... 10
  temp[0].count = (input.count + 1) / 2;         // (11+1) / 2 = 6
  temp[1].begin = temp[0].begin + temp[0].count; // 5  6  7    8 9
  temp[1].count = input.count / 2;               // 11 / 2 = 5

  return std::max(solve(temp[0], Max), solve(temp[1], Max));
}

int main() {
  DataSet data;
  given = {5, 33, 3, 45, 8, 9, 2, 1, 7, 0, 55};
  data.count = given.size();
  data.begin = 0;
  std::vector<DataType> Max;
  for (int i = 0; i < 3; i++) {
    Max.push_back(solve(data, Max));
    std::cout << Max[i] << " ";
  }
  return 0;
}
*/
