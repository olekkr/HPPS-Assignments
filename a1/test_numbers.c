#include <stdlib.h>
#include "numbers.h"

int test_on_domain(int a, int b, bool(*test)(unsigned char)){
    int fails = 0;
    for (int i = a; i < b; i++){
        if ( !(test)((unsigned char)i) ){
            fails += 1;
        }
    }
    return fails;
}

int test_on_domain2(int a, int b, bool(*test)(unsigned char, unsigned char)){
    int fails = 0;
    for (int ii = a; ii < b; ii++){
        for (int i = a; i < b; i++){
            if (!(test)((unsigned char)i, (unsigned char)ii)){
                fails += 1;
            }
        }
    }
    return fails;
}

bool test_conversion(unsigned char n){
    return bits8_to_int(bits8_from_int(n)) == n;
}

bool test_addition(unsigned char n, unsigned char nn){
    bool b = (n + nn) == bits8_to_int(bits8_add(bits8_from_int(n), bits8_from_int(nn)));
    return b
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
    printf("testing conversions ... finshed with %d failures.\n", test_on_domain(0, 255, test_conversion)); 
    printf("testing addition ... finshed with %d failures.\n", test_on_domain2(0, 64, test_addition));
    printf("testing addition- ... finshed with %d failures.\n", test_on_domain2(-64, 0, test_addition));
    printf("testing negation ... finshed with %d failures.\n", test_on_domain(0, 256, test_negation));
    printf("testing negation- ... finshed with %d failures.\n", test_on_domain(-256, 0, test_negation));
    // might not work due to overflows.
    printf("testing multiplication ... finshed with %d failures.\n", test_on_domain2(0, 256, test_multiplication));
    printf("testing multiplication-... finshed with %d failures.\n", test_on_domain2(-256, 0, test_multiplication));

    //test_on_domain(128, test_negation);
}
