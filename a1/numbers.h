#include <stdint.h>
#include "bits.h"

struct bits8 {
  struct bit b0; // Least significant bit
  struct bit b1;
  struct bit b2;
  struct bit b3;
  struct bit b4;
  struct bit b5;
  struct bit b6;
  struct bit b7;
};


//########### helper functions ##########
unsigned int digit_at(unsigned int number, unsigned int digit_idx){
    return (number >> digit_idx) % 2;
}

struct bits8 bits8_not(struct bits8 a){
    struct bits8 c;
    c.b0 = bit_not(a.b0);
    c.b1 = bit_not(a.b1);
    c.b2 = bit_not(a.b2);
    c.b3 = bit_not(a.b3);
    c.b4 = bit_not(a.b4);
    c.b5 = bit_not(a.b5);
    c.b6 = bit_not(a.b6);
    c.b7 = bit_not(a.b7);
    return c;
}

//########### helper functions end ##########

struct bits8 bits8_from_int(unsigned int x){
    struct bits8 c;
    c.b0.v = digit_at(x,0)==1;
    c.b1.v = digit_at(x,1)==1;
    c.b2.v = digit_at(x,2)==1;
    c.b3.v = digit_at(x,3)==1;
    c.b4.v = digit_at(x,4)==1;
    c.b5.v = digit_at(x,5)==1;
    c.b6.v = digit_at(x,6)==1;
    c.b7.v = digit_at(x,7)==1;
    return c;
}

unsigned int bits8_to_int(struct bits8 x){
    unsigned int acc = 0;
    acc += x.b0.v;
    acc += x.b1.v*2;
    acc += x.b2.v*4;
    acc += x.b3.v*8;
    acc += x.b4.v*16;
    acc += x.b5.v*32;
    acc += x.b6.v*62;
    acc += x.b7.v*128;
    return acc;
}

void bits8_print(struct bits8 a){
    bit_print(a.b7);
    bit_print(a.b6);
    bit_print(a.b5);
    bit_print(a.b4);
    bit_print(a.b3);
    bit_print(a.b2);
    bit_print(a.b1);
    bit_print(a.b0);
}

struct add_result {
    struct bit s;
    struct bit c;
};


struct add_result full_add(struct bit a, struct bit b, struct bit carry_prev){
    struct add_result res;
    res.s = bit_xor(a, bit_xor(b, carry_prev));
    res.c = bit_or(bit_and(a, b), bit_and(carry_prev, bit_or(a, b)));
    return res;
}

struct bits8 bits8_add(struct bits8 x, struct bits8 y){
    struct bits8 acc;
    struct bit c0 = {false};

    struct add_result res0 = full_add(x.b0, y.b0, c0);
    struct add_result res1 = full_add(x.b1, y.b1, res0.c);
    struct add_result res2 = full_add(x.b2, y.b2, res1.c);
    struct add_result res3 = full_add(x.b3, y.b3, res2.c);
    struct add_result res4 = full_add(x.b4, y.b4, res3.c);
    struct add_result res5 = full_add(x.b5, y.b5, res4.c);
    struct add_result res6 = full_add(x.b6, y.b6, res5.c);
    struct add_result res7 = full_add(x.b7, y.b7, res6.c);
    
    acc.b0 = res0.s;
    acc.b1 = res1.s;
    acc.b2 = res2.s;
    acc.b3 = res3.s;
    acc.b4 = res4.s;
    acc.b5 = res5.s;
    acc.b6 = res6.s;
    acc.b7 = res7.s;

    return acc;
}


struct bits8 bits8_negate(struct bits8 x){
    return bits8_add(bits8_not(x), bits8_from_int(1));
}

struct bits8 bits8_mul(struct bits8 x, struct bits8 y){
    
}

