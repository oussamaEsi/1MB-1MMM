#include "headers.h"

// Initialisation a Zero in Fp6
void initNulFp6 (elemFp6 *a){
    initNulFp2((*a).v0);
    initNulFp2((*a).v1);
    initNulFp2((*a).v2);
}

// Affectation in Fp6
void affectFp6 (elemFp6 a, elemFp6 *b){
    affectFp2(a.v0,(*b).v0);
    affectFp2(a.v1,(*b).v1);
    affectFp2(a.v2,(*b).v2);
}

// Addition in Fp6
void addFp6 (elemFp6 a, elemFp6 b, elemFp6 *res){

    addFp2(a.v0,b.v0,(*res).v0);
    addFp2(a.v1,b.v1,(*res).v1);
    addFp2(a.v2,b.v2,(*res).v2);

}

// Substraction in Fp6
void subFp6 (elemFp6 a, elemFp6 b, elemFp6 *res){

    subFp2(a.v0,b.v0,(*res).v0);
    subFp2(a.v1,b.v1,(*res).v1);
    subFp2(a.v2,b.v2,(*res).v2);

}

// Opposite in Fp6
void oppFp6(elemFp6 a, elemFp6 *oa){
    oppFp2(a.v0,(*oa).v0);
    oppFp2(a.v1,(*oa).v1);
    oppFp2(a.v2,(*oa).v2);
}

// Multiplication by redFp (Reduction)
void mulXFp6(elemFp6 a , elemFp6 *res){

    mulXFp2(a.v2,(*res).v0);
    affectFp2(a.v1,(*res).v2);
    affectFp2(a.v0,(*res).v1);

}

// Multiplication in Fp6
void mulFp6 (elemFp6 a, elemFp6 b, elemFp6 *res){

    ///**** ************* 1 2 3 *****************
    unsigned long t0[2][9],t1[2][9],t2[2][9];
    karatsubaFp2(a.v0,b.v0,t0);
    karatsubaFp2(a.v1,b.v1,t1);
    karatsubaFp2(a.v2,b.v2,t2);

    unsigned long temp[2][9],temp0[2][9];
    ///***************** 4 *****************
    addFp2(b.v1,b.v2,temp);
    addFp2(a.v1,a.v2,temp0);
    karatsubaFp2(temp0,temp,temp0);
    subFp2(temp0,t1,temp0);
    subFp2(temp0,t2,temp0);
    mulXFp2(temp0,temp0);
    addFp2(temp0,t0,(*res).v0);

    ///***************** 5 *****************
    addFp2(b.v0,b.v1,temp);
    addFp2(a.v0,a.v1,(*res).v1);
    karatsubaFp2((*res).v1,temp,(*res).v1);
    subFp2((*res).v1,t0,(*res).v1);
    subFp2((*res).v1,t1,(*res).v1);
    mulXFp2(t2,temp);
    addFp2((*res).v1,temp,(*res).v1);

    ///***************** 6 *****************
    addFp2(b.v0,b.v2,temp);
    addFp2(a.v0,a.v2,(*res).v2);
    karatsubaFp2((*res).v2,temp,(*res).v2);
    subFp2((*res).v2,t0,(*res).v2);
    subFp2((*res).v2,t2,(*res).v2);
    addFp2((*res).v2,t1,(*res).v2);


}

// Multiplication by b0(Fp2) in Fp6 { algo 14}
void mulFp6_b0 (elemFp6 a, unsigned long b0[2][9], elemFp6 *res){

    karatsubaFp2(a.v0, b0, (*res).v0);
    karatsubaFp2(a.v1, b0, (*res).v1);
    karatsubaFp2(a.v2, b0, (*res).v2);

}

// Multiplication by b0 and b1(Fp2) in Fp6 { algo 15}
void mulFp6_b0b1 (elemFp6 a, unsigned long b0[2][9], unsigned long b1[2][9], elemFp6 *res){
	unsigned long t0[2][9],t1[2][9];
	unsigned long tmp0[2][9],tmp1[2][9];

    karatsubaFp2(a.v0,b0,t0);
    karatsubaFp2(a.v1,b1,t1);

    addFp2(a.v1,a.v2,tmp0);
    karatsubaFp2(tmp0,b1,tmp0);
    subFp2(tmp0,t1,tmp0);
    mulXFp2(tmp0,tmp0);
    addFp2(tmp0,t0,(*res).v0);

    addFp2(a.v0,a.v1,tmp0);
    addFp2(b0,b1,tmp1);
    karatsubaFp2(tmp0,tmp1,tmp0);
    subFp2(tmp0,t0,tmp0);
    subFp2(tmp0,t1,(*res).v1);

    karatsubaFp2(a.v2,b0,tmp0);
    addFp2(tmp0,t1,(*res).v2);

}


// Squaring in Fp6
void squaFp6 (elemFp6 a, elemFp6 *res){
    unsigned long t0[2][9],t1[2][9],t2[2][9],t3[2][9];

    squarFp2(a.v0,t0);
    squarFp2(a.v2,t1);
    karatsubaFp2(a.v0,a.v1,t2);
    addFp2(t2,t2,t2);
    karatsubaFp2(a.v1,a.v2,t3);
    addFp2(t3,t3,t3);

    addFp2(a.v0,a.v2,(*res).v2);
    subFp2((*res).v2,a.v1,(*res).v2);
    squarFp2((*res).v2,(*res).v2);

    mulXFp2(t3,(*res).v0);
    addFp2((*res).v0,t0,(*res).v0);

    mulXFp2(t1,(*res).v1);
    addFp2((*res).v1,t2,(*res).v1);

    subFp2((*res).v2,t0,(*res).v2);
    subFp2((*res).v2,t1,(*res).v2);
    addFp2((*res).v2,t2,(*res).v2);
    addFp2((*res).v2,t3,(*res).v2);

}

// Inversion in Fp6
void invFp6(elemFp6 a, elemFp6 *invA){

    ///**************** 1 **********************
    unsigned long t0[2][9];
    squarFp2(a.v0,t0);

    ///**************** 2 **********************
    unsigned long t1[2][9];
    squarFp2(a.v1,t1);

    ///**************** 3 **********************
    unsigned long t2[2][9];
    squarFp2(a.v2,t2);

    ///**************** 4 **********************
    unsigned long t3[2][9];
    karatsubaFp2(a.v0,a.v1,t3);

    ///**************** 5 **********************
    unsigned long t4[2][9];
    karatsubaFp2(a.v0,a.v2,t4);

    ///**************** 6 **********************
    unsigned long t5[2][9];
    karatsubaFp2(a.v2,a.v1,t5);

    ///**************** 7 **********************
    mulXFp2(t5,t5);
    subFp2(t0,t5,t5);

    ///**************** 8 **********************
    mulXFp2(t2,t2);
    subFp2(t2,t3,t2);

    ///**************** 9 **********************
    subFp2(t1,t4,t1);

    ///**************** 10 **********************
    unsigned long t6[2][9];
    karatsubaFp2(a.v0,t5,t6);

    ///**************** 11 **********************
    karatsubaFp2(a.v2,t2,t0);
    mulXFp2(t0,t0);
    addFp2(t6,t0,t6);

    ///**************** 12 **********************
    karatsubaFp2(a.v1,t1,t0);
    mulXFp2(t0,t0);
    addFp2(t6,t0,t6);

    ///**************** 13 **********************
    invFp2(t6,t6);

    ///**************** 14  15 16 **********************
    karatsubaFp2(t5,t6,(*invA).v0);
    karatsubaFp2(t2,t6,(*invA).v1);
    karatsubaFp2(t1,t6,(*invA).v2);

}
