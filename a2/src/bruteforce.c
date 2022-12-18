#include "bruteforce.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>

int* knn(int k, int d, int n, const double *points, const double* query) {

  int* closest =  malloc(k * sizeof(double));

  //int candidate = 0;

  for (int i =0; i< k ; i ++){
    closest[i] = -1;
  }
  // skal den loope over 'candidate'? Skal funktionskaldet gemmes under et
  // navn fx "closest= ..."

  // måske skal n forbindes med candidates på en anden måde. forud for loopet nednefor.

  for (int candidate = 0; candidate < n; candidate ++) {
    insert_if_closer(k, d, points, closest,  query, points[candidate]);
  }
  return closest;
}
