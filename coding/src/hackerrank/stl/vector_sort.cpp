// Copyright 2019 Shun Kakinoki.

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  int size;
  cin >> size;

  int a;
  for (int i = 0; i < size; i++) {
    cin >> a;
    v.push_back(a);
  }

  sort(v.begin(), v.end());

  for (int i = 0; i < size; i++) {
    cout << v[i] << " ";
  }
  return 0;
}
