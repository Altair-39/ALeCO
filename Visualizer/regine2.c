#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constants
const int screenWidth = 800;
const int screenHeight = 800;
const int boardSize = 8;
const int squareSize = 800 / boardSize;
const int margin = 50;

// Colors
Color lightSquare = {238, 238, 210, 255};
Color darkSquare = {118, 150, 86, 255};
Color queenColor = {200, 0, 0, 255}; // Red color for queens

// Global variables
int tentativi = 0;
int queens[8]; // Array to store queen positions (queens[row] = column)
bool solutionFound = false;
int currentSolution = 0;
int totalSolutions = 0;
int **allSolutions = NULL;

// Function declarations
void DrawChessboard(void);
void DrawBoardBorder(void);
void DrawSquare(int row, int col);
void DrawFileCoordinates(void);
void DrawRankCoordinates(void);
void DrawQueens(void);
void DrawQueen(int row, int col);
Color GetSquareColor(int row, int col);
void DrawAllCoordinates(void);

// Queen problem functions
bool soluzione(int regine[], int j, int n, bool collectAll);
bool completa(int regine[], int j, int n);
bool rifiuta(int regine[], int j);
bool accetta(int regine[], int j);
void swap(int regine[], int i, int j);
void toString(int regine[], int j);
void findAllSolutions(void);
void findSolution(void);
void nextSolution(void);
void previousSolution(void);
void freeSolutions(void);

// Get the color for a specific square
Color GetSquareColor(int row, int col) {
  return ((row + col) % 2 == 0) ? lightSquare : darkSquare;
}

// Draw a single chessboard square
void DrawSquare(int row, int col) {
  Color squareColor = GetSquareColor(row, col);
  DrawRectangle(margin + col * squareSize, margin + row * squareSize,
                squareSize, squareSize, squareColor);
}

// Draw the chessboard
void DrawChessboard(void) {
  for (int row = 0; row < boardSize; row++) {
    for (int col = 0; col < boardSize; col++) {
      DrawSquare(row, col);
    }
  }
}

// Draw the border around the chessboard
void DrawBoardBorder(void) {
  DrawRectangle(margin - 2, margin - 2, screenWidth + 4, screenHeight + 4,
                BLACK);
}

// Draw file letters (a-h)
void DrawFileCoordinates(void) {
  for (int i = 0; i < boardSize; i++) {
    char fileChar = 'a' + i;
    DrawText(TextFormat("%c", fileChar),
             margin + i * squareSize + (squareSize >> 1) - 5,
             margin + screenHeight + 10, 20, BLACK);
  }
}

// Draw rank numbers (1-8)
void DrawRankCoordinates(void) {
  for (int i = 0; i < boardSize; i++) {
    char rankChar = '8' - i;
    DrawText(TextFormat("%c", rankChar), margin - 20,
             margin + i * squareSize + (squareSize >> 1) - 10, 20, BLACK);
  }
}

// Draw all coordinates
void DrawAllCoordinates(void) {
  DrawFileCoordinates();
  DrawRankCoordinates();
}

// Draw a queen on a specific square
void DrawQueen(int row, int col) {
  int centerX = margin + col * squareSize + (squareSize >> 1);
  int centerY = margin + row * squareSize + (squareSize >> 1);
  int radius = squareSize / 3;

  // Draw queen crown (simplified)
  DrawCircle(centerX, centerY, radius, queenColor);
  DrawCircle(centerX, centerY, radius - 2, GetSquareColor(row, col));

  // Draw crown points
  for (int i = 0; i < 5; i++) {
    float angle = i * 72 * 3.14159f / 180.0f;
    int pointX = centerX + (int)(radius * 0.8f * sinf(angle));
    int pointY = centerY - (int)(radius * 0.8f * cosf(angle));
    DrawCircle(pointX, pointY, radius >> 2, queenColor);
  }
}

// Draw all queens on the board
void DrawQueens(void) {
  if (!solutionFound)
    return;

  for (int row = 0; row < boardSize; row++) {
    int col = queens[row];
    DrawQueen(row, col);
  }
}

// Main game loop
void UpdateDrawFrame(void) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawBoardBorder();
  DrawChessboard();
  DrawQueens();
  DrawAllCoordinates();

  // Draw solution info
  if (solutionFound) {
    DrawText("8 Queens Solution Found!", margin, 20, 24, DARKBLUE);
    DrawText(TextFormat("Solution: %d/%d", currentSolution + 1, totalSolutions),
             margin, 50, 20, DARKBLUE);
    DrawText(TextFormat("Attempts: %d", tentativi), margin, 80, 20, DARKBLUE);
    DrawText("SPACE: Find all solutions", margin, 110, 20, DARKBLUE);
    if (totalSolutions > 1) {
      DrawText("LEFT/RIGHT: Navigate solutions", margin, 140, 20, DARKBLUE);
    }
  } else {
    DrawText("Press SPACE to find all solutions", margin, 20, 24, DARKBLUE);
  }

  EndDrawing();
}

// Queen problem functions

void toString(int *regine, int j) {
  for (int i = 0; i < j; i++) {
    printf("(%d, %d) ", i, regine[i]);
  }
}

bool completa(int *regine, int j, int n) { return j == n; }

bool rifiuta(int *regine, int j) {
  bool rif = false;
  for (int i = 0; i < j - 1 && !rif; i++) {
    rif = regine[j - 1] == regine[i] ||
          abs(regine[j - 1] - regine[i]) == abs(j - 1 - i);
  }
  return rif && j >= 2;
}

bool accetta(int *regine, int j) {
  bool acc = true;
  for (int i = 0; i < j - 1 && acc; i++) {
    acc = regine[j - 1] != regine[i] &&
          abs(regine[j - 1] - regine[i]) != abs(j - 1 - i);
  }
  return j <= 1 || acc;
}

void swap(int *regine, int i, int j) {
  int tmp = regine[i];
  regine[i] = regine[j];
  regine[j] = tmp;
}

// Modified soluzione to collect all solutions
bool soluzione(int regine[], int j, int n, bool collectAll) {
  if (!completa(regine, j, n)) {
    if (!rifiuta(regine, j)) {
      bool foundSolution = false;
      for (int i = 0; i < n; i++) {
        regine[j] = i;
        foundSolution = soluzione(regine, j + 1, n, collectAll);
        if (foundSolution && !collectAll) {
          return true; // Return early if we found one and not collecting all
        }
      }
      return foundSolution;
    } else {
      toString(regine, j);
      printf("<-- rifiuta. Tentativo %d\n", ++tentativi);
      return false;
    }
  } else {
    bool accepted = accetta(regine, j);
    if (accepted) {
      toString(regine, j);
      printf("<-- accetta. Tentativo %d\n", ++tentativi);

      // Save solution if collecting all
      if (collectAll) {
        totalSolutions++;
        allSolutions = realloc(allSolutions, totalSolutions * sizeof(int *));
        allSolutions[totalSolutions - 1] = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
          allSolutions[totalSolutions - 1][i] = regine[i];
        }
      }
      return true;
    } else {
      toString(regine, j);
      printf("<-- rifiuta. Tentativo %d\n", ++tentativi);
      return false;
    }
  }
}

// Find and display all solutions
void findAllSolutions(void) {
  tentativi = 0;
  solutionFound = false;
  currentSolution = 0;
  totalSolutions = 0;
  freeSolutions();

  // Initialize queens array
  for (int i = 0; i < boardSize; i++) {
    queens[i] = -1;
  }

  printf("Finding all solutions for 8 queens problem...\n");
  soluzione(queens, 0, boardSize, true); // true = collect all solutions

  if (totalSolutions > 0) {
    solutionFound = true;
    // Load the first solution
    for (int i = 0; i < boardSize; i++) {
      queens[i] = allSolutions[0][i];
    }
    printf("Found %d solutions!\n", totalSolutions);
  } else {
    printf("No solutions found after %d attempts.\n", tentativi);
  }
}

// Find a single solution (original behavior)
void findSolution(void) {
  tentativi = 0;
  solutionFound = false;
  currentSolution = 0;
  totalSolutions = 0;
  freeSolutions();

  for (int i = 0; i < boardSize; i++) {
    queens[i] = -1;
  }

  printf("Finding a solution for 8 queens problem...\n");
  solutionFound =
      soluzione(queens, 0, boardSize, false); // false = find one solution

  if (solutionFound) {
    printf("Solution found after %d attempts!\n", tentativi);
    printf("Queen positions: ");
    for (int i = 0; i < boardSize; i++) {
      printf("(%d, %d) ", i, queens[i]);
    }
    printf("\n");
  } else {
    printf("No solution found after %d attempts.\n", tentativi);
  }
}

// Navigate to next solution
void nextSolution(void) {
  if (solutionFound && totalSolutions > 1) {
    currentSolution = (currentSolution + 1) % totalSolutions;
    for (int i = 0; i < boardSize; i++) {
      queens[i] = allSolutions[currentSolution][i];
    }
    printf("Displaying solution %d/%d\n", currentSolution + 1, totalSolutions);
  }
}

// Navigate to previous solution
void previousSolution(void) {
  if (solutionFound && totalSolutions > 1) {
    currentSolution = (currentSolution - 1 + totalSolutions) % totalSolutions;
    for (int i = 0; i < boardSize; i++) {
      queens[i] = allSolutions[currentSolution][i];
    }
    printf("Displaying solution %d/%d\n", currentSolution + 1, totalSolutions);
  }
}

// Free allocated memory for solutions
void freeSolutions(void) {
  if (allSolutions != NULL) {
    for (int i = 0; i < totalSolutions; i++) {
      free(allSolutions[i]);
    }
    free(allSolutions);
    allSolutions = NULL;
  }
  totalSolutions = 0;
  currentSolution = 0;
}

int main(void) {
  InitWindow(screenWidth + (margin << 1), screenHeight + (margin << 1),
             "8 Queens Problem - Multiple Solutions");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Check for key presses
    if (IsKeyPressed(KEY_SPACE)) {
      findAllSolutions(); // Find ALL solutions
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      nextSolution(); // Next solution
    }
    if (IsKeyPressed(KEY_LEFT)) {
      previousSolution(); // Previous solution
    }

    UpdateDrawFrame();
  }

  // Clean up
  freeSolutions();
  CloseWindow();
  return 0;
}
