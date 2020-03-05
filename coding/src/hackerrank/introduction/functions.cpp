// Copyright 2019 Shun Kakinoki.
// Reference: https://www.hackerrank.com/challenges/c-tutorial-functions/forum

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int max_of_four(int a, int b, int c, int d) {
  int z = 0;
  int t1 = a > b ? a : b;
  int t2 = c > d ? c : d;
  z = t1 > t2 ? t1 : t2;
  return z;
}

int main() {
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  int ans = max_of_four(a, b, c, d);
  printf("%d", ans);

  return 0;
}
