// Copyright 2019 Shun Kakinoki.
// Reference: https://www.hackerrank.com/challenges/variable-sized-arrays/forum

#include <iostream>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;

  // Create 2d Array
  int** a = new int*[n];

  // Fill 2d Array with 1d Subarrays
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;

    // Create the 1d Subarray with the Given Length
    int* i_arr = new int[k];

    // Fill the Subarray with K Values
    for (int j = 0; j < k; j++) {
      cin >> i_arr[j];
    }

    a[i] = i_arr;
  }

  for (int q_num = 0; q_num < q; q_num++) {
    int i, j;
    cin >> i >> j;
    cout << a[i][j] << endl;
  }

  // Delete 2d Array (Each Subarray Must Be Deleted)
  for (int i = 0; i < n; i++) {
    delete[] a[i];
  }
  delete[] a;

  return 0;
}
