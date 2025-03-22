#include "../header/ReginePerEsiste.h"
#include <stdbool.h>
#include <stdio.h>

int tentativi;

int main() {
  // Array to hold the different sizes of the board to test
  int sizes[] = {1, 2, 3, 4, 5, 8};
  int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

  // Loop through each board size and solve the N-Queens problem
  for (int i = 0; i < num_sizes; i++) {
    int n = sizes[i]; // Get the current board size (n x n)
    int regine[n];    // Array to hold the positions of queens
    tentativi = 0;    // Reset the attempt counter for each size

    // Initialize the array with -1 (indicating no queen placed)
    for (int j = 0; j < n; j++) {
      regine[j] = -1;
    }

    printf("Attempting to solve the %d-Queens problem...\n", n);

    // Call the backtracking function to try and solve the problem
    if (soluzione(regine, 0, n)) {
      printf("Solution found after %d attempts for %d-Queens problem.\n",
             tentativi, n);
    } else {
      printf("No solution found after %d attempts for %d-Queens problem.\n",
             tentativi, n);
    }
    printf("\n");
  }

  return 0;
}
