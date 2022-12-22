#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
  // d is a pointer to a location in the heap that we have just allocated.
  struct naive_data* d = malloc(sizeof(struct naive_data));
  d->rs=rs;
  d->n=n;
  // we set values via s->a which is the same (*s).a
  return d;
}

void free_naive(struct naive_data* data) {
  // the struct naive_data "data" is the only thing which we have allocated
  // and thus needs to be freed.
  free(data);
  return;
}

const struct record* lookup_naive(struct naive_data *data, int64_t needle) {
  // For convenince we redifne data->rs to just rs
  const struct record* rs = data->rs;
  // same for the int n
  int n = data->n;

  
  for(int i = 0; i<n; i++){
      // its rs[i].osm_id and not rs[i]-> 
      // because subscripting "[]" also derefrences it (along with shifting the location proportional to i)
      // (same as "*")
      // so rs[i].osm is a shorthand for *(rs+( i*sizeof(record) ))
      if(rs[i].osm_id == needle){
          return &rs[i];
      }
  }
  // if it checks each needle and never matches
  // it returns a null-pointer.
  return NULL;
}

int main(int argc, char** argv) {
  // remember that mk_naive, free_naive, lookup_naive are all function pointers "casted".
  // in other words regarded by C as a [mk_index_fn, free_index_fn, lookup_fn] function from id_query.c
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_naive,
                    (free_index_fn)free_naive,
                    (lookup_fn)lookup_naive);
}
