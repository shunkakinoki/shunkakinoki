// Copyright 2019 Shun Kakinoki.
// Reference: https://atcoder.jp/contests/abc001/submissions/8498695

#include <bits/stdc++.h>
using namespace std;

using ld = long double;

signed main() {
  int deg, dis;
  cin >> deg >> dis;
  deg *= 10;
  deg += 1125;
  deg %= 36000;
  string s[16] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
                  "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};
  int ans = 0;
  ld a = dis;
  ld k[13] = {0,    0.3,  1.6,  3.4,  5.5,  8.0, 10.8,
              13.9, 17.2, 20.8, 24.5, 28.5, 32.7};
  for (int i = 0; i < 13; i++)
    if (a >= (k[i] - 0.050000001) * 60) ans = i;
  if (ans == 0)
    cout << "C"
         << " " << ans << endl;
  else
    cout << s[deg / 2250] << " " << ans << endl;
}
