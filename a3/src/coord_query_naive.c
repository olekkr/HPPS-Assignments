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

// like in the other naive code
struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
  // like before
  struct naive_data* nd = malloc(sizeof(struct naive_data));
  nd->rs = rs;
  nd->n =  n;
  return nd;
}

// 
void free_naive(struct naive_data* data) {
  // free(data->rs); //oops. dont free data that is passed to you. 
  free(data);
}


// lon and lat has beend flipped for some reason???
const struct record* lookup_naive(struct naive_data *data, double lon, double lat) {
  int n = data->n;
  struct record* rs = data->rs; // a pointer to the record collection
  long double cand_dist = LDBL_MAX; // this is the maximum value a long double can be, imported from float.h
  struct record* cand = NULL; 
  // ^define a variable that holds a pointer to a record, for now its 0.
  
  // iterate over each elem and only update cand_dist and cand if distance lower
  for(int i=0; i < n; i++){
      // here lon and lat has switched places, im not sure why i had to do that but it works now 
      long double sq_dist = pow(rs[i].lon - lat, 2) + pow(rs[i].lat - lon, 2);
      //^minimizing a^2 + b^2 is the same as that squared because sq() is monotonically increasing 
      // in the positive domain
      // pow is defined in https://linux.die.net/man/3/pow and imported with math.h
      if (sq_dist < cand_dist){ // update only if the sq_dist is lesser
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
