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
    struct bits8 c = {
            {false},{false},{false},{false},
            {false},{false},{false},{false}
    };
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

struct bits8 bits8_and(struct bits8 a, struct bits8 b){
    struct bits8 c = {
            {false},{false},{false},{false},
            {false},{false},{false},{false}
    };
    c.b0 = bit_and(a.b0, b.b0);
    c.b1 = bit_and(a.b1, b.b1);
    c.b2 = bit_and(a.b2, b.b2);
    c.b3 = bit_and(a.b3, b.b3);
    c.b4 = bit_and(a.b4, b.b4);
    c.b5 = bit_and(a.b5, b.b5);
    c.b6 = bit_and(a.b6, b.b6);
    c.b7 = bit_and(a.b7, b.b7);
    return c;
}
struct bits8 bits8_or(struct bits8 a, struct bits8 b){
    struct bits8 c = {
            {false},{false},{false},{false},
            {false},{false},{false},{false}
    };
    c.b0 = bit_or(a.b0, b.b0);
    c.b1 = bit_or(a.b1, b.b1);
    c.b2 = bit_or(a.b2, b.b2);
    c.b3 = bit_or(a.b3, b.b3);
    c.b4 = bit_or(a.b4, b.b4);
    c.b5 = bit_or(a.b5, b.b5);
    c.b6 = bit_or(a.b6, b.b6);
    c.b7 = bit_or(a.b7, b.b7);
    return c;
}
struct bits8 bits8_xor(struct bits8 a, struct bits8 b){
    struct bits8 c = {
            {false},{false},{false},{false},
            {false},{false},{false},{false}
    };
    c.b0 = bit_xor(a.b0, b.b0);
    c.b1 = bit_xor(a.b1, b.b1);
    c.b2 = bit_xor(a.b2, b.b2);
    c.b3 = bit_xor(a.b3, b.b3);
    c.b4 = bit_xor(a.b4, b.b4);
    c.b5 = bit_xor(a.b5, b.b5);
    c.b6 = bit_xor(a.b6, b.b6);
    c.b7 = bit_xor(a.b7, b.b7);
    return c;
}
//########### helper functions end ##########

struct bits8 bits8_from_int(unsigned int x){
    struct bits8 c = {
            {false},{false},{false},{false},
            {false},{false},{false},{false}
    };
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
    printf("\n0b%u%u%u%u%u%u%u%u\n", a.b7.v, a.b6.v, a.b5.v, a.b4.v, a.b3.v, a.b2.v, a.b1.v, a.b0.v);
}
struct bits8 bits8_add(struct bits8 x, struct bits8 y){
    struct bits8 carry = bits8_and(x,y);
    struct bits8 shifted_c = bits8_from_int(bits8_to_int * 2);


}

struct bits8 bits8_negate(struct bits8 x);

struct bits8 bits8_mul(struct bits8 x, struct bits8 y);

