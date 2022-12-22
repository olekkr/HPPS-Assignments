#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"
// think about how this looks like in memory vs a record
struct index_record {
  int64_t osm_id;
  const struct record *record;
};
// index record looks like [(int 64/ 8 bytes), (pointer/ 64 bits also)
// And record ...
//
// const char *name;
//  const char *alternative_names;
//  const char *osm_type;
//  int64_t osm_id;
//  const char *class;
//  const char *type;
//  double lon;
//  double lat;
// etc.....
// So huge...
// Think about the "stride" (stepsize, when you traverse it) is
// vs a tiny index_record
  
struct index_data{
  struct index_record* ids;
  int n;
};

struct index_data* mk_index(struct record* rs, int n) {
    // malloc to store the collection of index_records
    struct index_record* i_records = malloc(n*sizeof(struct index_record));
    for(int i = 0; i<n; i++){
        // write all the records...
        i_records[i].osm_id = rs[i].osm_id;
        i_records[i].record = &rs[i];
    }
    // malloc space on heap to store the index_data that holds the 
    // collection and size of the collection
    struct index_data* irs = malloc(sizeof(struct index_data));
    irs->ids = i_records;
    irs->n = n;
    return irs;
}

void free_index(struct index_data* data) {
    // for each malloc there is a free which should be correct.
    free(data->ids);
    free(data);
}

const struct record* lookup_index(struct index_data *data, int64_t needle) {
    // write in the report about stride here vs on the one before.
    // and why this is faster
    for(int i=0; i<data->n; i++){
        if(data->ids[i].osm_id==needle){
            return data->ids[i].record;
        }
    }
    // if nothing is found return 0 or a (NULL pointer)
    return NULL;
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_index,
                    (free_index_fn)free_index,
                    (lookup_fn)lookup_index);
}
