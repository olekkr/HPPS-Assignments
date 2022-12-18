#include "util.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

double distance(int d, const double *x, const double *y) {
  // min accumlerede værdi til brug i loopet initialiseres her?
  double acc = 0;
  int i;
  for (i = 1; i <= d; i ++){
      acc = acc + pow(x[i] - y[i], 2);
  }

  return (sqrt(acc));
}

// closest bliver givet udefra initialisering -1 overalt. Den ER sorteret så at
// den altid har det mindste først. Hvis bare denne her funktion virker.

int insert_if_closer(int k, int d,
                     const double *points, int *closest, const double *query,
                     int candidate) {
  // altså noget med
  double candDist;

  // jeg skal indexerer ind i candiate

  candDist = distance(d, query, &points[candidate]);

  for(int i = 0; i <= k; i ++){
    if (closest[i] == -1) {
        closest[i] = candidate;

      return(1);
    }
    candDist = distance(d, query, &points[closest[i]*d]);

    if (candDist < closest[candidate]){
        for (int j = k-1; j<= i; j--)  {
           closest[j] = closest[j-1];
         }
      closest[i] = candidate;
      return(1);
    }
    return(0);
  }
}
