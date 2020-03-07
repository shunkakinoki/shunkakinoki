// Copyright 2019 Shun Kakinoki.
// Reference: https://www.hackerrank.com/challenges/cpp-lower-bound/forum

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    v.push_back(x);
  }

  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    int qi;
    cin >> qi;
    vector<int>::iterator low = lower_bound(v.begin(), v.end(), qi);
    if (v[low - v.begin()] == qi)
      cout << "Yes " << (low - v.begin() + 1) << endl;
    else
      cout << "No " << (low - v.begin() + 1) << endl;
  }

  return 0;
}
