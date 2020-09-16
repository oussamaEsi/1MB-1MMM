#include "headers.h"

// Frobenius raised to p of f dans Fp12
void frob_p (elemFp12 a, elemFp12 *res){

    ///*************** iNit ***********************
    conjugFp2(a.w0.v0,(*res).w0.v0); //t1
    conjugFp2(a.w1.v0,(*res).w1.v0); //t2
    conjugFp2(a.w0.v1,(*res).w0.v1); //t3
    conjugFp2(a.w1.v1,(*res).w1.v1); //t4
    conjugFp2(a.w0.v2,(*res).w0.v2); //t5
    conjugFp2(a.w1.v2,(*res).w1.v2); //t6

    ///************** Calculs **********************
    mulCFp2((*res).w1.v0,y11,(*res).w1.v0);
    mulCFp2((*res).w0.v1,y12,(*res).w0.v1);
    mulCFp2((*res).w1.v1,y13,(*res).w1.v1);
    mulCFp2((*res).w0.v2,y14,(*res).w0.v2);
    mulCFp2((*res).w1.v2,y15,(*res).w1.v2);

}

// Frobenius raised to p(2) of f dans Fp12
void frob_p2 (elemFp12 a, elemFp12 *res){

	affectFp2(a.w0.v0,(*res).w0.v0);
    mulCFp2(a.w1.v0,y21,(*res).w1.v0);
    mulCFp2(a.w0.v1,y22,(*res).w0.v1);
    mulCFp2(a.w1.v1,y23,(*res).w1.v1);
    mulCFp2(a.w0.v2,y24,(*res).w0.v2);
    mulCFp2(a.w1.v2,y25,(*res).w1.v2);

}
