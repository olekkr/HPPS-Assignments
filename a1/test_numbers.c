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

bool test_test(unsigned char n){
    return false;
}

bool test_test2(unsigned char n, unsigned char nn){
    return false;
}

int test_on_domain(int a, bool(*test)(unsigned char)){
    int fails = 0;
    for (int i = 0; i < 256; i++){
        if ( !(test)((unsigned char)i) ){
            fails += 1;
            //printf("%d\n", i);
        }
    }
    return fails;
}

int test_on_domain2(int a, bool(*test)(unsigned char, unsigned char)){
    int fails = 0;
    for (int ii = 0; ii < a; ii++){
        for (int i = 0; i < a; i++){
            if (!(test)((unsigned char)i, (unsigned char)ii)){
                fails += 1;
                //printf("%d, %d\n", i, ii);
            }
        }
    }
    return fails;
}

bool test_conversion(unsigned char n){
    return bits8_to_int(bits8_from_int(n)) == n;
}

bool test_addition(unsigned char n, unsigned char nn){
    return (n + nn) == bits8_to_int(bits8_add(bits8_from_int(n), bits8_from_int(nn)));
}

bool test_negation(unsigned char n){
    signed char a = -((signed char)n) ;
    signed char b = bits8_to_int(bits8_negate(bits8_from_int(n)));
    return a==b;
}

bool test_multiplication(unsigned char n, unsigned char nn){
    return bits8_to_int(bits8_mul(bits8_from_int(n), bits8_from_int(nn))) == n * nn;
}


int main() {
    struct bits8 bits = bits8_not(test1);
    bits8_print(bits);
    printf("\n");
    bits8_print(bits8_from_int((unsigned int)2));

    printf("\n");
    printf("%d", bits8_to_int(test2));
    
    printf("\n");
    bits8_print(bits8_add(test2, test1));
    printf("\n");
    
    printf("testing conversions ... finshed with %d failures.\n", test_on_domain(255, test_conversion));
    
    printf("testing addition ... finshed with %d failures.\n", test_on_domain2(64, test_addition));

    printf("testing negation ... finshed with %d failures.\n", test_on_domain(256, test_negation));

    // might not work due to overflows.
    printf("testing multiplication ... finshed with %d failures.\n", test_on_domain2(256, test_multiplication));

    //test_on_domain(128, test_negation);
}
