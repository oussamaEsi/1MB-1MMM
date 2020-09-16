#include "headers.h"

// Initialisation à Zero
void initNulFp2 (unsigned long a[2][9]){
    int i;
    for(i=0;i<9;i++) a[0][i]=0;
    for(i=0;i<9;i++) a[1][i]=0;
}

// Affectation Fp2
void affectFp2(unsigned long a[2][9], unsigned long b[2][9]){
    setIN(a[0],b[0]);
    setIN(a[1],b[1]);
}

// Comparesion
int equalsFp2 (unsigned long a[2][9], unsigned long b[2][9]){
    int i,j;
    for(i=0;i<2;i++)
        for(j=0;j<8;j++)
        	if(a[i][j]!=b[i][j]) return 0;
    return 1;
}

// Addition in Fp2
void addFp2 (unsigned long a[2][9] , unsigned long b[2][9] , unsigned long res[2][9]){

    addFp(a[0],b[0],p,res[0]);
    addFp(a[1],b[1],p,res[1]);

}

// Substarction in Fp2
void subFp2 (unsigned long a[2][9] , unsigned long b[2][9] , unsigned long res[2][9]){

    subFp(a[0],b[0],p,res[0]);
    subFp(a[1],b[1],p,res[1]);

}

// Opposite in Fp2
void oppFp2 (unsigned long a[2][9] , unsigned long oa[2][9]){
    subFp(p,a[0],p,oa[0]);
    subFp(p,a[1],p,oa[1]);
}

// Conjugate in Fp2
void conjugFp2 (unsigned long a[2][9] , unsigned long aa[2][9]){
    setIN(a[0],aa[0]);
    subFp(p,a[1],p,aa[1]);
}

// Multiplication by coeff
void mulCFp2 (unsigned long a[2][9], unsigned long coeff[9], unsigned long b[2][9]){

	Montgomery(a[0], coeff,b[0]);
	Montgomery(a[1], coeff,b[1]);

}

// Multiplication by redFp (Reduction)
void mulXFp2(unsigned long a[2][9], unsigned long aX[2][9]){
    unsigned long tmp[9]={0};

    Montgomery(a[1],redFp,tmp);
    setIN(a[0],aX[1]);
    setIN(tmp,aX[0]);

}

// Multiplication in Fp2
void karatsubaFp2 (unsigned long a[2][9] , unsigned long b[2][9] , unsigned long res[2][9]){
        unsigned long t0[9],t1[9],temp[9];

        Montgomery(a[0],b[0],t0); //t0 <- a0*b0
        Montgomery(a[1],b[1],t1); //t1 <- a1*b1

        addFp(b[0],b[1],p,temp); // tmp <-b0+b1
        addFp(a[0],a[1],p,res[1]); // res1 <-a0+a1
        Montgomery(res[1],temp,res[1]);
        subFp(res[1],t0,p,res[1]);
        subFp(res[1],t1,p,res[1]);

        Montgomery(t1,redFp,res[0]);
        addFp(res[0],t0,p,res[0]);

}

// Squaring in Fp2
void squarFp2 (unsigned long a[2][9], unsigned long c[2][9]){
    unsigned long v0[9],tmp[9];

    Montgomery(a[0],a[1],v0); // v0=a0*a1

    Montgomery(redFp,a[1],tmp); // tmp <- a1*redFp
    addFp(a[0],tmp,p,tmp);
    addFp(a[0],a[1],p,c[0]);
    Montgomery(c[0],tmp,c[0]);

    Montgomery(redFp,v0,tmp);
    subFp(c[0],v0,p,c[0]);
    subFp(c[0],tmp,p,c[0]);

    addFp(v0,v0,p,c[1]); // c1 = 2v0
}

// Inversion in Fp2
void invFp2 (unsigned long a[2][9], unsigned long invA[2][9]){
    unsigned long t0[9],t1[9];

    ///******************* calcul coeff******************
    Montgomery(a[0],a[0],t0);
    Montgomery(a[1],a[1],t1);
    Montgomery(redFp,t1,t1);
    subFp(t0,t1,p,t0);

    invFp(t0,t0);

    ///**************   Affectations ***************
    Montgomery(a[0],t0,invA[0]);

    Montgomery(a[1],t0,invA[1]);
    subFp(p,invA[1],p,invA[1]);

}

/// proelem faut voir unite montgomery!!!!!!!!!!!!!!!!!!!
/*void expoFp2 (unsigned long a[2][9], unsigned long exposant[9] ,unsigned long res[2][9]){
    unsigned long i,j,puis2[2][9];
    ///******************* INit
    setIN(a[0],puis2[0]);
    setIN(a[1],puis2[1]);
    for(i=0;i<2;i++) for(j=0;j<9;j++) res[i][j]=0;
    setIN(R,res[0]);
    ///************* exponitiation
    for(i=0;i<8;i++){
        for(j=0;j<32;j++){
            if(getBitIndex(exposant[i],j) == 1) karatsubaFp2(res,puis2,res);
            karatsubaFp2(puis2,puis2,puis2);
        }
    }
}*/
