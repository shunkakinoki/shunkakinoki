// Copyright 2019 Shun Kakinoki.

#include <algorithm>
#include <cstdio>

bool f[60 * 24 / 5];

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d-%d", &a, &b);
    a = ((a / 100) * 60 + (a % 100)) / 5;
    b = ((b / 100) * 60 + (b % 100) + 4) / 5;
    std::fill(f + a, f + b, true);
  }

  for (int i = 0; i < 60 * 24 / 5;) {
    if (!f[i]) {
      ++i;
      continue;
    }
    int j = i;
    while (j < 60 * 24 / 5 && f[j]) ++j;
    auto g = [](int a) { return (a / 12) * 100 + (a % 12 * 5); };
    printf("%04d-%04d\n", g(i), g(j));
    i = j;
  }

  return 0;
}
