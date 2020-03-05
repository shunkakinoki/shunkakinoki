// Copyright 2019 Shun Kakinoki.

// FAIL
#include <stdio.h>
#include <cmath>

void update(int *a, int *b) {
  int *ua = &a;
  int *ub = &b;

  *a = *ua + *ub;
  *b = abs(*ua - *ub);
}

int main() {
  int a, b;
  int *pa = &a, *pb = &b;

  scanf("%d %d", &a, &b);
  update(pa, pb);
  printf("%d\n%d", a, b);

  return 0;
}
