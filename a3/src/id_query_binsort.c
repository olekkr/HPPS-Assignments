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
// a function to compare two records. used for qsort its the one called compar 
// https://linux.die.net/man/3/qsort
int comp(const void* a, const void* b){
    int64_t comp = ((struct index_record*) a)->osm_id - ((struct index_record*) b)->osm_id;
    if (comp < 0){ return -1; }
    else if (comp == 1) { return 0; }
    else {return 1;}
}
// almost same as indexed
struct index_data* mk_index(struct record* rs, int n) {
    struct index_record* i_records = malloc(n*sizeof(struct index_record));
    for(int i = 0; i<n; i++){
        i_records[i].osm_id = rs[i].osm_id;
        i_records[i].record = &rs[i];
    }
    struct index_data* irs = malloc(sizeof(struct index_data));
    irs->ids = i_records;
    irs->n = n;
    
    // only difference from before is that we sort it here.
    // Sorting time
    qsort(i_records, n, sizeof(struct index_record), comp);
    
    return irs;
}

// same as id_query_index
void free_index(struct index_data* data) {
    free(data->ids);
    free(data);
}

//recursive binary search algortihm on an array of index_records
const struct index_record* bin_search (struct index_record* index_set, int set_len, int64_t target){
    if (set_len == 0){return NULL;}  // if len reaches 0 then the element does not exist.
    int64_t middle_element = index_set[set_len/2].osm_id;
    if (middle_element == target){
        return &index_set[set_len/2];
    }
    if (set_len == 1){return NULL;} // possibly extraneous controlflow
    if (middle_element > target){
        // left (lesser) half
        return bin_search(index_set, set_len/2, target);
    }
    if (middle_element < target){
        // right (greater) half
        return bin_search(&index_set[set_len/2], set_len-(set_len/2), target);
        //the & means we are taking the position of the element not the actual element.
    }
    // code is kinda wack, im pretty sure you remove some if statements and simplify it.
    return NULL;
}

const struct record* lookup_index(struct index_data *data, int64_t needle) {
    int n = data->n;
    struct index_record* ids = data->ids;
    // again for ease of use rename the variables.
    const struct index_record* result = bin_search(ids, n, needle);
    // ^ this can return a pointer or a null pointer
  
    if(result){
        // if ^ result is null then it does the else statement
        return result->record;
    }
    else{
        return NULL;
    }
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_index,
                    (free_index_fn)free_index,
                    (lookup_fn)lookup_index);
}
