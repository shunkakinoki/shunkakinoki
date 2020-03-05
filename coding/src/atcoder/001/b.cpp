// Copyright 2019 Shun Kakinoki.
// Reference: https://atcoder.jp/contests/abc001/submissions/8704524

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  int VV;

  if (n > 70000)
    VV = 89;
  else if (n >= 35000)
    VV = (n / 1000 - 30) / 5 + 80;
  else if (n >= 6000)
    VV = n / 1000 + 50;
  else if (n >= 100)
    VV = n / 100;
  else if (n < 100)
    VV = 0;

  printf("%02d\n", VV);
  return 0;
}
