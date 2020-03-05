// Copyright 2019 Shun Kakinoki.

#include <bits/stdc++.h>
using namespace std;

int main() {
  int m;
  cin >> m;
  if (m < 100) {
    cout << "00" << endl;
  } else if (100 <= m < 1000) {
    m = m / 100;
    cout << '0' << m << endl;
  } else if (1000 <= m <= 5000) {
    m = m / 100;
    cout << m << endl;
  } else if (6000 <= m <= 30000) {
    m = m / 1000;
    cout << m << endl;
    cout << m + 50 << endl;
  } else if (35000 <= m <= 70000) {
    m = m / 1000;
    cout << (m - 30) / 5 + 80 << endl;
  } else if (m > 70000) {
    cout << "89" << endl;
  }
  return 0;
}
