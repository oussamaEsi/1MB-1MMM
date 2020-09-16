#include <stdio.h>
#include "headers.h"

// Initialisation
void initNul (unsigned long a[9]){
    unsigned long i;
    for(i=0;i<9;i++) a[i]=0;
}

// Initialisation
void initNul2D(unsigned long a[][9] , unsigned long nbL , unsigned long nbC){
    unsigned long i,j;
    for(i=0;i<nbL;i++)
        for(j=0;j<nbC;j++) a[i][j]=0;
}

// Print Fp
void PRINT(unsigned long *c){
    unsigned long i;
    printf("aff: \n");
    for(i=0;i<9;i++){
            printf("%lu ",c[i]);
    }
    printf("\n");
}

// Print Hex Fp
void PRINTHex(unsigned long *c){
    unsigned long i;
    printf("aff: \n");
    for(i=0;i<9;i++){
            printf("%08lx ",c[8-i]);
    }
    printf("\n");
}

// Print Fp2
void PRINT2D(unsigned long c[][9],unsigned long k){
    unsigned long i,j;
    printf("Pol: \n");
    fflush(stdout);
    for(i=0;i<k;i++){
            for(j=0;j<9;j++){
                    printf("%lu ",c[i][8-j]);//printf("%08x ",c[i][j]);
                    fflush(stdout);
            }
    printf("\n");
    }
    printf("\n");
}

// Print Hex Fp2
void PRINTHex2D(unsigned long c[][9],unsigned long k){
    unsigned long i,j;
    printf("Pol: \n");
    fflush(stdout);
    for(i=0;i<k;i++){

            for(j=0;j<9;j++){
                    printf("%08lx ",c[i][8-j]);//printf("%08x ",c[i][j]);
                    fflush(stdout);
            }
    printf("\n");
    }
    printf("\n");
}

// Print Hex Fp12
void printHexFp12(elemFp12 l){
    printf("Resultat : \n");
    PRINTHex2D(l.w0.v0,2);
    PRINTHex2D(l.w0.v1,2);
    PRINTHex2D(l.w0.v2,2);
    PRINTHex2D(l.w1.v0,2);
    PRINTHex2D(l.w1.v1,2);
    PRINTHex2D(l.w1.v2,2);
}

