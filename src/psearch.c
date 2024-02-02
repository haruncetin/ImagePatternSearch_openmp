#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "include/psearch.h"

void p_search(uint16_t **I, unsigned int N, uint16_t **P, unsigned int K) {

  int i, j, m, n;

  // Threshold for the difference between pixels
  int threshold = 5;
  
  // Find the center of the kernels
  int kc = K / 2;

  // Get the number of threads
  int n_threads = omp_get_max_threads();
  printf("Number of threads: %d\n", n_threads);

  #pragma omp parallel for num_threads(n_threads) private(j, m, n) shared(I, P, N, K, threshold, kc) collapse(1)
  for (i = 0; i < N; i++) {
    // Search for the pattern in the lower triangle of the image matrix
    for (j = i; j < N; j++) {
      int matchInLowerTriangle = 1;
      for (m = 0; m < K; m++) {
        for (n = 0; n < K; n++) {
          int ii = i + (m - kc);
          int jj = j + (n - kc);

          // Check if the input element is within the matrix bounds
          if (ii >= 0 && ii < N && jj >= 0 && jj < N) {
            int diff = _abs(I[jj][ii] - P[n][m]);
            if (diff > threshold) {
              matchInLowerTriangle = 0;
              break;
            }
          } 
        }
      }
      if (matchInLowerTriangle) {
        #pragma omp critical
        printf("Found in LOWER TRIANGLE at row: %d, col: %d\n", i-kc, j-kc);
      }
    }

    // Search for the pattern in the lower triangle of the image matrix
    for (j = 0; j <= i; j++) {
      int matchInUpperTriangle = 1;
      for (m = 0; m < K; m++) {
        for (n = 0; n < K; n++) {
          int ii = i + (m - kc);
          int jj = j + (n - kc);

          // Check if the input element is within the matrix bounds
          if (ii >= 0 && ii < N && jj >= 0 && jj < N) {
            int diff = _abs(I[jj][ii] - P[n][m]);
            if (diff > threshold) {
              matchInUpperTriangle = 0;
              break;
            }
          } 
        }
      }
      if (matchInUpperTriangle) {
        #pragma omp critical
        printf("Found in UPPER TRIANGLE at row: %d, col: %d\n", i-kc, j-kc);
      }
    }
  }
}

