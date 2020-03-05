// Copyright 2019 Shun Kakinoki.
// Reference:
// https://www.hackerrank.com/challenges/c-tutorial-conditional-if-else/forum

#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string num[10] = {"Greater than 9", "one", "two",   "three", "four",
                    "five",           "six", "seven", "eight", "nine"};
  if (n > 9) {
    cout << num[0];
  } else {
    cout << num[n];
  }

  return 0;
}
