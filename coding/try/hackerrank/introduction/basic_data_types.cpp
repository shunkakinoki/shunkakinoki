// Copyright 2019 Shun Kakinoki.

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int a;
  long b;  // NOLINT(runtime/int)
  char c;
  float d;
  double e;

  scanf("%d %ld %c %f %lf", &a, &b, &c, &d, &e);
  printf("%d\n%ld\n%c\n%f\n%lf", a, b, c, d, e);

  return 0;
}
