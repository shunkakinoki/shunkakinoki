// Copyright 2019 Shun Kakinoki.
// Reference: https://www.hackerrank.com/challenges/c-tutorial-for-loop/forum

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a;
  cin >> b;

  string num[9] = {"one", "two",   "three", "four", "five",
                   "six", "seven", "eight", "nine"};

  for (int i = a; i <= b; i++) {
    if (i <= 9)
      cout << num[i - 1] << endl;
    else if (i % 2 == 0)
      cout << "even\n";
    else
      cout << "odd\n";
  }

  return 0;
}
