// Copyright 2019 Shun Kakinoki.
// Reference: https://www.hackerrank.com/challenges/cpp-sets/forum

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
  int q;
  cin >> q;

  set<int> ss;

  for (int i = 0; i < q; ++i) {
    int type, query;
    cin >> type >> query;

    switch (type) {
      case 1:
        ss.insert(query);
        break;
      case 2:
        ss.erase(query);
        break;
      case 3:
        cout << (ss.find(query) == ss.end() ? "No" : "Yes") << endl;
        break;
    }
  }

  return 0;
}
