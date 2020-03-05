// Copyright 2019 Shun Kakinoki.
// Reference: https://www.hackerrank.com/challenges/arrays-introduction/forum

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, i = 0;
  cin >> N;
  int *A = new int[N];
  while (cin >> A[i++] && (i < N)) {
  }
  while (cout << A[--N] << ' ' && N) {
  }
  delete[] A;
  return 0;
}
