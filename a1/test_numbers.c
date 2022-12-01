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
    printf("\n");
    bits8_print(bits8_from_int((unsigned int)2));

    printf("\n");
    printf("%d", bits8_to_int(test2));
    
    printf("\n\n");
    bits8_print(bits8_add(test2, test1));

}
