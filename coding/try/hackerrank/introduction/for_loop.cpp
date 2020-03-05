// Copyright 2019 Shun Kakinoki.

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a;
  cin >> b;

  string num[10] = {"Greater than 9", "one", "two",   "three", "four",
                    "five",           "six", "seven", "eight", "nine"};

  for (int i = a; i <= b; i++) {
    if (i > 9 && i % 2 == 0) {
      cout << "even" << endl;
    } else if (i > 9 && i % 2 == 1) {
      cout << "odd" << endl;
    } else {
      cout << num[i] << endl;
    }
  }

  return 0;
}
