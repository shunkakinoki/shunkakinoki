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

  vector<int> x;
  for (int i = 0; i < n; i++) {
    int xi;
    cin >> xi;
    x.push_back(xi);
  }

  sort(x.begin(), x.end());

  int q;
  cin >> q;

  for (int i = 0; i < n; i++) {
    cout << v[i] << ' ';
  }

  return 0;
}