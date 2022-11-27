#include "numbers.h"


struct bit test_bit = {true};

struct bits8 a = {
    {true}, {false}, {false}, {false},
    {false}, {false}, {false}, {false}
};



int main (){
    bit_print(a.b0);
    return(3);
}
