#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct index_record {
  int64_t osm_id;
  const struct record *record;
};

struct index_data{
  struct index_record* ids;
  int n;
};

struct index_data* mk_index(struct record* rs, int n) {
    struct index_record* i_records = malloc(n*sizeof(struct index_record));
    for(int i = 0; i<n; i++){
        i_records[i].osm_id = rs[i].osm_id;
        i_records[i].record = &rs[i];
    }
    struct index_data* irs = malloc(sizeof(struct index_data));
    irs->ids = i_records;
    irs->n = n;
    return irs;
}

void free_index(struct index_data* data) {
    free(data->ids);
    free(data);
}

const struct record* lookup_index(struct index_data *data, int64_t needle) {
    for(int i=0; i<data->n; i++){
        if(data->ids[i].osm_id==needle){
            return data->ids[i].record;
        }
    }
    return NULL;
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_index,
                    (free_index_fn)free_index,
                    (lookup_fn)lookup_index);
}
