#include "header/common.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GenPair area0[4], area1[4], area2[4];
GenPair *areas[3];

void init() {
  area0[0].first = malloc(sizeof(size_t));
  area0[1].first = malloc(sizeof(size_t));
  area0[2].first = malloc(sizeof(size_t));
  area0[3].first = malloc(sizeof(size_t));

  area1[0].first = malloc(sizeof(size_t));
  area1[1].first = malloc(sizeof(size_t));
  area1[2].first = malloc(sizeof(size_t));
  area1[3].first = malloc(sizeof(size_t));

  area2[0].first = malloc(sizeof(size_t));
  area2[1].first = malloc(sizeof(size_t));
  area2[2].first = malloc(sizeof(size_t));
  area2[3].first = malloc(sizeof(size_t));

  area0[0].second = malloc(sizeof(size_t));
  area0[1].second = malloc(sizeof(size_t));
  area0[2].second = malloc(sizeof(size_t));
  area0[3].second = malloc(sizeof(size_t));

  area1[0].second = malloc(sizeof(size_t));
  area1[1].second = malloc(sizeof(size_t));
  area1[2].second = malloc(sizeof(size_t));
  area1[3].second = malloc(sizeof(size_t));

  area2[0].second = malloc(sizeof(size_t));
  area2[1].second = malloc(sizeof(size_t));
  area2[2].second = malloc(sizeof(size_t));
  area2[3].second = malloc(sizeof(size_t));

  // Assign areas to the areas array
  areas[0] = area0;
  areas[1] = area1;
  areas[2] = area2;

  // Initialize the values for area0
  *(size_t *)area0[0].first = 8;
  *(size_t *)area0[0].second = 10;
  *(size_t *)area0[1].first = 10;
  *(size_t *)area0[1].second = 43;
  *(size_t *)area0[2].first = 20;
  *(size_t *)area0[2].second = 51;
  *(size_t *)area0[3].first = 22;
  *(size_t *)area0[3].second = 63;

  // Initialize the values for area1
  *(size_t *)area1[0].first = 11;
  *(size_t *)area1[0].second = 39;
  *(size_t *)area1[1].first = 21;
  *(size_t *)area1[1].second = 12;
  *(size_t *)area1[2].first = 0;
  *(size_t *)area1[2].second = 0;
  *(size_t *)area1[3].first = 0;
  *(size_t *)area1[3].second = 0;

  // Initialize the values for area2
  *(size_t *)area2[0].first = 8;
  *(size_t *)area2[0].second = 27;
  *(size_t *)area2[1].first = 10;
  *(size_t *)area2[1].second = 9;
  *(size_t *)area2[2].first = 20;
  *(size_t *)area2[2].second = 47;
  *(size_t *)area2[3].first = 0;
  *(size_t *)area2[3].second = 0;
}

void freeMemory() {
  size_t i = 0;

  while (i < 4) {
    free(area0[i].first);
    free(area1[i].first);
    free(area2[i].first);
    free(area0[i].second);
    free(area1[i].second);
    free(area2[i].second);
    i++;
  }
}

size_t minWeight(GenPair *area, size_t length) {
  size_t min = *(size_t *)area[0].first;
  size_t i = 1;

  while (i < length) {
    if (*(size_t *)area[i].first < min)
      min = *(size_t *)area[i].first;
    i++;
  }

  return min;
}

size_t sumMinWeight(GenPair **areas, size_t lengthTot, size_t *length) {
  size_t sum = 0;
  size_t i = 0;

  while (i < lengthTot) {
    sum += minWeight(areas[i], length[i]);
    i++;
  }

  return sum;
}

size_t maxWeight(GenPair *area, size_t length) {
  size_t max = *(size_t *)area[0].first;
  size_t i = 1;

  while (i < length) {
    if (*(size_t *)area[i].first > max)
      max = *(size_t *)area[i].first;
    i++;
  }

  return max;
}

size_t sumMaxWeight(GenPair **areas, size_t lengthTot, size_t *length) {
  size_t sum = 0;
  size_t i = 0;

  while (i < lengthTot) {
    sum += maxWeight(areas[i], length[i]);
    i++;
  }

  return sum;
}

char *listOutOfBudget(int budget, GenPair **areas, size_t *areaLengths,
                      size_t numAreas) {
  size_t maxLen = 1000;
  char *u = (char *)malloc(maxLen * sizeof(char));
  size_t area = 0, i = 0;
  if (u == NULL) {
    return NULL; 
  }
  strcpy(u, "Given the budget ");
  char buffer[50];

  sprintf(buffer, "%d,\n", budget);
  strcat(u, buffer);

  while (area < numAreas) {
    strcat(u, "-) from area ");
    sprintf(buffer, "%zu", area);
    strcat(u, buffer);
    strcat(u, " discard proposals: ");

    int sumMinAreas = 0;
    while (i < numAreas) {
      if (i != area)
        sumMinAreas += minWeight(areas[i], areaLengths[i]);
      i++;
    }

    i = 0;

    while (i < areaLengths[area]) {
      if (*(size_t *)areas[area][i].first > budget) {
        strcat(u, "proposal ");
        sprintf(buffer, "%zu", i);
        strcat(u, buffer);
        strcat(u, ", ");
      }
      i++;
    }

    if (u[strlen(u) - 2] == ',') {
      u[strlen(u) - 2] = '.'; 
    }

    strcat(u, "\n");
    area++;
  }
  return u;
}

int main(int argc, char *argv[]) {
  size_t budget = 10;
  size_t lengthT[3] = {4, 4, 4};
  char *list;

  init();

  printf("Il budget distribuibile deve essere compreso tra %zu e %zu\n",
         sumMinWeight(areas, 3, lengthT), sumMaxWeight(areas, 3, lengthT));

  while (budget <= 22) {
    list = listOutOfBudget(budget, areas, lengthT, 3);
    if (list) {
      printf("%s", list);
      free(list);
    }
    budget++;
  }

  freeMemory();

  return EXIT_SUCCESS;
}
