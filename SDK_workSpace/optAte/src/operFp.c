#include "headers.h"

///*********************************** addition / soustraction  **********************************///
int isNul (unsigned long a[9]) {
    int i;
    for(i=0;i<8;i++) if (a[i]!=0) return 0;
    return 1;
}

unsigned long getBitIndex(unsigned long num,int index){
	unsigned long bit = (num>>index)&1;
	return bit;
}

int equalsFp(unsigned long a[9], unsigned long b[9]) {
    int i;
    for(i=0; i<8; i++)
        if (a[i]!=b[i]) return 0;
    return 1;
}

void add2Op(unsigned long A,unsigned long B,unsigned long *retenue,unsigned long *resultat) {
	unsigned long long r = (unsigned long long) A+B+(*retenue);
	*resultat = (int) r;
	*retenue = r>>32;
}

void sous2Op(unsigned long A, unsigned long B, unsigned long *retenue, unsigned long *resultat) {
	unsigned long long r = (unsigned long long) A+(4294967295-B)+(*retenue);
	*resultat=(int) r;
	*retenue=r>>32;
}

void setIN(unsigned long A[9], unsigned long B[9]) {
	int i;
	for(i=0; i<9; i++)
		B[i] = A[i];
}

/// addition in Fp
unsigned long addFp( unsigned long A[9], unsigned long B[9], unsigned long M[9], unsigned long SZ[9]) {
	unsigned long SZ1[9], SZ2[9];
	unsigned long i, C1=0, C2=1, sign;

	for(i=0; i<9; i++){
		add2Op( A[i], B[i], &C1, &SZ1[i] );
		sous2Op( SZ1[i], M[i], &C2, &SZ2[i]);
	}

	sign = getBitIndex( (C1+C2+3), 1);

	if(sign == 1) setIN( SZ1, SZ);
	else setIN( SZ2, SZ);

	return sign;
}


/// substarction in Fp
unsigned long subFp( unsigned long A[9], unsigned long B[9], unsigned long M[9], unsigned long SZ[9]) {
	unsigned long SZ1[9], SZ2[9];
	unsigned long i, C1=1, C2=0, sign;

	for(i=0; i<9; i++){
		sous2Op( A[i], B[i], &C1, &SZ1[i]);
		add2Op( SZ1[i], M[i], &C2, &SZ2[i]);
	}

	sign = getBitIndex( (C1+3), 0);

	if(sign == 1) setIN( SZ2, SZ);
	else setIN( SZ1, SZ);

	return sign;
}


///******************************************* Operations of Montgomery *********************************///


// Exponontiation in Fp
void expFp (unsigned long a[9], unsigned long exposant[9] ,unsigned long res[9]){
    unsigned long i,j,puis2[9];

    ///******************* INit *******************
    setIN(a,puis2);
    setIN(R,res);
    ///************* exponitiation  ***************
    for(i=0;i<8;i++){
        for(j=0;j<32;j++){
            if(getBitIndex(exposant[i],j) == 1) Montgomery(res,puis2,res);
            Montgomery(puis2,puis2,puis2);
        }
    }
}

// Inverse Exponotiation in Fp
void invFp (unsigned long a[9], unsigned long invA [9]){

    expFp(a,p_2,invA);
}

// Enter in Montgomery field
void transfMongPol (unsigned long A[][9],unsigned long k){
    int i;
    for(i=0;i<k;i++) Montgomery( A[i], R2, A[i]);
}

// Get out Montgomery field
void invTransMongPol (unsigned long A[][9] ,unsigned long B[][9], unsigned long k){
    unsigned long i;
    for(i=0;i<k;i++) Montgomery( A[i], UN, B[i]);
}

