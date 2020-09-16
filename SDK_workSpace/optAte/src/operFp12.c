#include "headers.h"


// Initialisation a Zero in Fp12
void initNulFp12 (elemFp12 *a){
    initNulFp6(&((*a).w0));
    initNulFp6(&((*a).w1));
}

// Affectation in Fp6
void affectFp12(elemFp12 a, elemFp12 *b){
    affectFp6(a.w0,&((*b).w0));
    affectFp6(a.w1,&((*b).w1));
}

// Addition in Fp12
void addFp12 (elemFp12 a, elemFp12 b, elemFp12 *res){
    addFp6(a.w0,b.w0,&((*res).w0));
    addFp6(a.w1,b.w1,&((*res).w1));
}

// Opposite in Fp12
void oppFp12 (elemFp12 a, elemFp12 *oa){
    oppFp6(a.w0,&((*oa).w0));
    oppFp6(a.w1,&((*oa).w1));
}

// Substraction in Fp12
void subFp12(elemFp12 a, elemFp12 b, elemFp12 *res){

    subFp6(a.w0,b.w0,&((*res).w0));
    subFp6(a.w1,b.w1,&((*res).w1));

}

// Conjugate in Fp12
void conjugFp12 (elemFp12 a, elemFp12 *res){
    affectFp6(a.w0,&((*res).w0));
    oppFp6(a.w1,&((*res).w1));
}

// Multiplication in Fp12
void mulFp12 (elemFp12 a, elemFp12 b, elemFp12 *res){

    elemFp6 t0,t1;
    mulFp6(a.w0,b.w0,&t0);
    mulFp6(a.w1,b.w1,&t1);


    elemFp6 temp1,temp2;
    mulXFp6(t1,&((*res).w0));
    addFp6(t0,((*res).w0),&((*res).w0));

    addFp6(a.w0,a.w1,&temp2);
    addFp6(b.w0,b.w1,&((*res).w1));
    mulFp6(temp2,(*res).w1,&((*res).w1));
    subFp6((*res).w1,t0,&((*res).w1));
    subFp6((*res).w1,t1,&((*res).w1));

}


// Multiplication by b=b0+b1w / b0 in Fp2 / b1= b10+ b11v+ 0v(2)
void mulFp12_b0b1 (elemFp12 a, elemFp12 b, elemFp12 *res){

	unsigned long b00[2][9],b10[2][9],b11[2][9],t2[2][9];
	affectFp2(b.w0.v0, b00);
	affectFp2(b.w1.v0, b10);
	affectFp2(b.w1.v1, b11);


    elemFp6 t0,t1,tmp;
    mulFp6_b0(a.w0,b00,&t0);
    mulFp6_b0b1(a.w1,b10,b11,&t1);

    mulXFp6(t1,&tmp);
    addFp6(t0,tmp, &(*res).w0);


    addFp2(b00,b10,t2);
    addFp6(a.w0,a.w1,&tmp);
    mulFp6_b0b1(tmp,t2,b11,&tmp);
    subFp6(tmp,t0,&tmp);
    subFp6(tmp,t1,&(*res).w1);



}


// Squaring in Fp12
void squarFp12 (elemFp12 a, elemFp12 *res){

    elemFp6 t0,tmp;
    mulFp6(a.w0,a.w1,&t0);
    mulXFp6(a.w1,&tmp);

    subFp6(a.w0,tmp,&tmp);
    subFp6(a.w0,a.w1,&((*res).w0));
    mulFp6((*res).w0,tmp,&((*res).w0));

    addFp6(t0,t0,&((*res).w1));

    mulXFp6(t0,&tmp);
    addFp6((*res).w0,t0,&((*res).w0));
    addFp6((*res).w0,tmp,&((*res).w0));

}

// Squaring in Fp12 -- Version 2
void squarFp12_V2 (elemFp12 f, elemFp12 *res){

	unsigned long v0[2][9],v1[2][9],v2[2][9];
	unsigned long A0[2][9],A1[2][9],B0[2][9],B1[2][9],C0[2][9],C1[2][9];
	unsigned long u0[2][9],u1[2][9],u2[2][9];
	unsigned long tmp[2][9], tmp0[2][9];

	karatsubaFp2(f.w0.v0,f.w1.v0,v0);
	karatsubaFp2(f.w0.v1,f.w1.v1,v1);
	karatsubaFp2(f.w0.v2,f.w1.v2,v2);

	addFp2(f.w0.v0,f.w1.v0,A0);
	mulXFp2(f.w1.v0,tmp);
	addFp2(f.w0.v0,tmp,A1);
	addFp2(f.w0.v1,f.w1.v1,B0);
	mulXFp2(f.w1.v1,tmp);
	addFp2(f.w0.v1,tmp,B1);
	addFp2(f.w0.v2,f.w1.v2,C0);
	mulXFp2(f.w1.v2,tmp);
	addFp2(f.w0.v2,tmp,C1);

	karatsubaFp2(A0,A1,u0);
	karatsubaFp2(B0,B1,u1);
	karatsubaFp2(C0,C1,u2);

	mulXFp2(v0,tmp);
	addFp2(v0,tmp,A0);
	mulXFp2(v1,tmp);
	addFp2(v1,tmp,B0);
	mulXFp2(v2,tmp);
	addFp2(v2,tmp,C0);

	// --- c0
	subFp2(u0,A0,tmp);
	addFp2(tmp,tmp,tmp0);
	addFp2(tmp0,tmp,tmp0);
	subFp2(tmp0,f.w0.v0,tmp0);
	subFp2(tmp0,f.w0.v0,(*res).w0.v0);

	// --- c1
	addFp2(v2,v2,tmp);
	addFp2(tmp,v2,tmp);
	addFp2(tmp,tmp,tmp);
	addFp2(tmp,f.w0.v1,tmp);
	addFp2(tmp,f.w0.v1,(*res).w0.v2);

	// --- c2
	subFp2(u1,B0,tmp);
	addFp2(tmp,tmp,tmp0);
	addFp2(tmp0,tmp,tmp0);
	subFp2(tmp0,f.w0.v2,tmp0);
	subFp2(tmp0,f.w0.v2,(*res).w1.v1);

	// --- c3
	addFp2(v0,v0,tmp);
	addFp2(tmp,v0,tmp);
	addFp2(tmp,tmp,tmp);
	addFp2(tmp,f.w1.v0,tmp);
	addFp2(tmp,f.w1.v0,(*res).w0.v1);

	// --- c4
	subFp2(u2,C0,tmp);
	addFp2(tmp,tmp,tmp0);
	addFp2(tmp0,tmp,tmp0);
	subFp2(tmp0,f.w1.v1,tmp0);
	subFp2(tmp0,f.w1.v1,(*res).w1.v0);

	// --- c5
	addFp2(v1,v1,tmp);
	addFp2(tmp,v1,tmp);
	addFp2(tmp,tmp,tmp);
	addFp2(tmp,f.w1.v2,tmp);
	addFp2(tmp,f.w1.v2,(*res).w1.v2);

}

// Inversion in Fp12
void invFp12 (elemFp12 a, elemFp12 *invA){

    elemFp6 t0,t1,tmp;
    squarFp6(a.w0,&t0);
    squarFp6(a.w1,&t1);
    mulXFp6(t1,&tmp);
    subFp6(t0,tmp,&t0);
    invFp6(t0,&t1);
    mulFp6(a.w0,t1,&((*invA).w0));
    mulFp6(a.w1,t1,&((*invA).w1));
    oppFp6((*invA).w1,&((*invA).w1));

}

/*
// Exponontiaion 't' in Fp12
void expTFp12(elemFp12 a, elemFp12 *res){

    unsigned long i,j;
    elemFp12 puis2;
    ///******************* INit *******************
    affectFp12(a,&puis2);
    initNulFp12(res);
    for(i=0;i<8;i++) (*res).w0.v0[0][i] = R[i];
    ///************* exponitiation  ***************
    for(j=0;j<32;j++) squarFp12(puis2,&puis2);
    for(j=0;j<30;j++){
        if(getBitIndex(t[1],j) == 1) mulFp12(*res,puis2,res);
        squarFp12(puis2,&puis2);
    }
}
*/
// Exponontiaion 't' in Fp12
void expTFp12(elemFp12 a, elemFp12 *res){

    int j=0;
    elemFp12 ca;
    ///******************* INit *******************
    affectFp12(a,res);

    ///************* exponitiation  ***************
    for(j=61;j>=0;j--){
    	//squarFp12(*res,res);
    	squarFp12_V2(*res,res);
    	if(j==54) {
    		conjugFp12(a,&ca);
    		mulFp12(ca,(*res),res);
    	}
    	if(j==44) {
    		mulFp12(a,(*res),res);
    	}
    }

}

/*
// Exponotiation 'exposant' in Fp12
void expoFp12(elemFp12 a, unsigned long exposant[9] ,elemFp12 *res){
    unsigned long i,j;
    elemFp12 puis2;
    ///******************* INit *******************
    affectFp12(a,&puis2);
    initNulFp12(res);
    for(i=0;i<8;i++) (*res).w0.v0[0][i] = R[i];
    ///************* exponitiation  ***************
    for(i=0;i<8;i++){
        for(j=0;j<32;j++){
            if(getBitIndex(exposant[i],j) == 1) mulFp12(*res,puis2,res);
            squarFp12(puis2,&puis2);
        }
    }
}
*/


// Enter in Montgomery field Fp12
void transfMongFp12 (elemFp12 *P){
    transfMongPol((*P).w0.v0,2);
    transfMongPol((*P).w0.v1,2);
    transfMongPol((*P).w0.v2,2);
    transfMongPol((*P).w1.v0,2);
    transfMongPol((*P).w1.v1,2);
    transfMongPol((*P).w1.v2,2);
}

// Get out Montgomery field Fp12
void invTransMongFp12(elemFp12 l, elemFp12 *n){
    invTransMongPol(l.w0.v0,(*n).w0.v0,2);
    invTransMongPol(l.w0.v1,(*n).w0.v1,2);
    invTransMongPol(l.w0.v2,(*n).w0.v2,2);
    invTransMongPol(l.w1.v0,(*n).w1.v0,2);
    invTransMongPol(l.w1.v1,(*n).w1.v1,2);
    invTransMongPol(l.w1.v2,(*n).w1.v2,2);
}

/*
// Squaring in Fp4 // algo 9
void squarFp4 (elemFp4 a, elemFp4 *res){

	unsigned long t0[2][9],t1[2][9];
	unsigned long tmp1[2][9],tmp2[2][9];

	squarFp2(a.v0, t0);
	squarFp2(a.v1, t1);

	mulXFp2(t1,tmp1);
	addFp2(tmp1,t0,(*res).v0);

	addFp2(a.v0,a.v1,tmp2);
	squarFp2(tmp2,tmp2);
	subFp2(tmp2,t0,tmp2);
	subFp2(tmp2,t1,(*res).v1);

}

// Squaring in Fp12 // algo 24
void squarFp12_V2 (elemFp12 a, elemFp12 *res){

	elemFp4 A, B, C;

	affectFp2(a.w0.v0, A.v0);
	affectFp2(a.w1.v1, A.v1);
	squarFp4(A,&A);

	affectFp2(a.w1.v0, B.v0);
	affectFp2(a.w0.v2, B.v1);
	squarFp4(B,&B);

	affectFp2(a.w0.v1, C.v0);
	affectFp2(a.w1.v2, C.v1);
	squarFp4(C,&C);
	mulXFp2(C.v1,C.v1);

    unsigned long tmp1[2][9];
    addFp2(A.v0,A.v0,tmp1);
    addFp2(tmp1,A.v0,tmp1);
    unsigned long tmp2[2][9];
    addFp2(a.w0.v0,a.w0.v0,tmp2);
    subFp2(tmp1,tmp2,(*res).w0.v0);

    addFp2(B.v1,B.v1,tmp1);
    addFp2(tmp1,B.v1,tmp1);
    addFp2(a.w0.v1,a.w0.v1,tmp2);
    subFp2(tmp1,tmp2,(*res).w0.v1);

    addFp2(C.v0,C.v0,tmp1);
    addFp2(tmp1,C.v0,tmp1);
    addFp2(a.w0.v2,a.w0.v2,tmp2);
    subFp2(tmp1,tmp2,(*res).w0.v2);

    addFp2(C.v1,C.v1,tmp1);
    addFp2(tmp1,C.v1,tmp1);
    addFp2(a.w1.v0,a.w1.v0,tmp2);
    addFp2(tmp1,tmp2,(*res).w1.v0);

    addFp2(A.v1,A.v1,tmp1);
    addFp2(tmp1,A.v1,tmp1);
    addFp2(a.w1.v1,a.w1.v1,tmp2);
    addFp2(tmp1,tmp2,(*res).w1.v1);

    addFp2(B.v0,B.v0,tmp1);
    addFp2(tmp1,B.v0,tmp1);
    addFp2(a.w1.v2,a.w1.v2,tmp2);
    addFp2(tmp1,tmp2,(*res).w1.v2);

}
*/

