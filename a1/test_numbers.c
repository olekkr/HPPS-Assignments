#include <stdlib.h>
#include "numbers.h"

struct bits8 test0 = {       
    {false},{false},{false},{false},
    {false},{false},{false},{false},
};

struct bits8 test1 = {       
    {true},{false},{false},{false},
    {false},{false},{false},{false},
};

struct bits8 test2 = {       
    {true}, {false}, {false}, {true}, 
    {true}, {false}, {false}, {true}
};


int main() {
    struct bits8 bits = bits8_not(test1);
    bits8_print(bits);
    bits8_print(bits8_from_int(2));

    printf("%b", bits8_to_int(test2));

}
