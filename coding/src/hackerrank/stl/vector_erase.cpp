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

  int z;
  for (int i = 0; i < size; i++) {
    cin >> z;
    v.push_back(z);
  }

  int x;
  cin >> x;
  v.erase(v.begin() + x - 1);

  int a, b;
  cin >> a >> b;
  v.erase(v.begin() + a - 1, v.begin() + b - 1);

  cout << v.size() << endl;
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  return 0;
}
