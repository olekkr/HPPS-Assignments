#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include <float.h> //for LDBL_MAX
#include <math.h> 

#include "record.h"
#include "coord_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data* nd = malloc(sizeof(struct naive_data));
  nd->rs = rs;
  nd->n =  n;
  return nd;
}

void free_naive(struct naive_data* data) {
  free(data->rs);
  free(data);
}


// lon and lat has beend flipped for some reason???
const struct record* lookup_naive(struct naive_data *data, double lon, double lat) {
  int n = data->n;
  struct record* rs = data->rs;
  long double cand_dist = LDBL_MAX;
  struct record* cand = NULL;

  for(int i=0; i < n; i++){
      long double sq_dist = pow(rs[i].lon - lat, 2) + pow(rs[i].lat - lon, 2);
      if (sq_dist < cand_dist){
          cand_dist = sq_dist;
          cand = &rs[i];
      }
  }
  return cand;
}

int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_naive,
                          (free_index_fn)free_naive,
                          (lookup_fn)lookup_naive);
}
