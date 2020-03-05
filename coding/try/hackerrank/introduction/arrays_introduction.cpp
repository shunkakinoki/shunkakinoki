// Copyright 2019 Shun Kakinoki.

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  int a[n];  // NOLINT(runtime/arrays)

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = n - 1; i >= 0; i--) {
    cout << a[i] << ' ';
  }

  return 0;
}
