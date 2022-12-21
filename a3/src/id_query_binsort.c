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

int comp(const void* a, const void* b){
    int64_t comp = ((struct index_record*) a)->osm_id - ((struct index_record*) b)->osm_id;
    if (comp < 0){ return -1; }
    else if (comp == 1) { return 0; }
    else {return 1;}
}

struct index_data* mk_index(struct record* rs, int n) {
    struct index_record* i_records = malloc(n*sizeof(struct index_record));
    for(int i = 0; i<n; i++){
        i_records[i].osm_id = rs[i].osm_id;
        i_records[i].record = &rs[i];
    }
    struct index_data* irs = malloc(sizeof(struct index_data));
    irs->ids = i_records;
    irs->n = n;
    
    // Sorting time
    qsort(i_records, n, sizeof(struct index_record), comp);
    
    return irs;
}

void free_index(struct index_data* data) {
    free(data->ids);
    free(data);
}

const struct index_record* bin_search (struct index_record* index_set, int set_len, int64_t target){
    int64_t middle_element = index_set[set_len/2].osm_id;

    if (set_len <= 1){return NULL;}
    if (middle_element > target){
        // left (lesser) half
        return bin_search(index_set, set_len/2, target);
    }
    if (middle_element < target){
        // right (greater) half
        return bin_search(&index_set[set_len/2], set_len-(set_len/2), target);
    }

    if (middle_element == target){
        return &index_set[set_len/2];
    }
    else {
        assert(0);
    }


}

const struct record* lookup_index(struct index_data *data, int64_t needle) {
    int n = data->n;
    struct index_record* ids = data->ids;
    
    return bin_search(ids, n, needle)->record;

}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_index,
                    (free_index_fn)free_index,
                    (lookup_fn)lookup_index);
}
