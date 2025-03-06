#include <algorithm> //sort
#include <cctype>    // isalpha
#include <fstream>   // ifstream, ofstream
#include <iomanip>   // setw
#include <iostream>
#include <map>
#include <sstream> // stringstream
#include <vector>

using namespace std;

// 計算並輸出單詞計數直方圖
void write_word_histogram(ofstream &output, map<string, int> &wordCount) {
  for (const auto &pair : wordCount) {
    output << setw(10) << left << pair.first; // 左對齊，單詞
    for (int i = 0; i < pair.second; i++) {
      output << "*"; // 輸出星號表示次數
    }
    output << " " << pair.second << endl; // 輸出數字次數
  }
}

// 排序並輸出字母統計
void write_char_statistics(ofstream &output, map<char, int> &charCount) {
  vector<pair<char, int>> vec(charCount.begin(), charCount.end());

  // 按出現次數排序
  sort(vec.begin(), vec.end(),
       [](const pair<char, int> &a, const pair<char, int> &b) {
         return a.second < b.second;
       });

  // 輸出排序結果
  for (const auto &pair : vec) {
    output << pair.first << "   " << pair.second << endl;
  }
}

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile.is_open()) {
    cerr << "Failed to open input file." << endl;
    return 1;
  }

  ofstream wordOutputFile("hist.txt");
  if (!wordOutputFile.is_open()) {
    cerr << "Failed to open word output file." << endl;
    return 1;
  }

  ofstream charOutputFile("freg.txt");
  if (!charOutputFile.is_open()) {
    cerr << "Failed to open char output file." << endl;
    return 1;
  }

  map<string, int> wordCount;
  map<char, int> charCount;
  string line, word;

  // 讀取文件，計算單詞和字母次數
  while (getline(inputFile, line)) {
    stringstream ss(line);
    while (ss >> word) {
      // 計算單詞次數，將單詞轉換為小寫以便不區分大小寫
      for (char &c : word) {
        c = tolower(c); // 全部轉為小寫
        if (isalpha(c)) {
          charCount[c]++; // 計算字母次數
        }
      }
      wordCount[word]++;
    }
  }

  // 寫入單詞直方圖到文件
  write_word_histogram(wordOutputFile, wordCount);
  wordOutputFile.close();

  // 寫入字母統計到文件
  write_char_statistics(charOutputFile, charCount);
  charOutputFile.close();

  inputFile.close();

  return 0;
}
