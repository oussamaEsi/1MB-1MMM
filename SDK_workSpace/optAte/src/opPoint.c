#include "headers.h"
#include <stdio.h>

// Affectation
void affPointFp2(PointFp2 P, PointFp2 *Q){
    affectFp2(P.x,(*Q).x);
    affectFp2(P.y,(*Q).y);
    affectFp2(P.z,(*Q).z);
}

// Opposé d'un point
void oppPointFp2 (PointFp2 P, PointFp2 *Q){
    affectFp2(P.x,(*Q).x);
    oppFp2(P.y,(*Q).y);
    affectFp2(P.z,(*Q).z);
}

// frobenius d'un pointFp2
void frobeniuspFp2 (PointFp2 Q, PointFp2 *frob){
    conjugFp2(Q.x,(*frob).x);
    mulCFp2((*frob).x,y12,(*frob).x);

    conjugFp2(Q.y,(*frob).y);
    mulCFp2((*frob).y,y13,(*frob).y);

    //conjugFp2(Q.z,(*frob).z);
}
/*
void affPointFp(PointFp P, PointFp *Q){
    setIN(P.x,(*Q).x);
    setIN(P.y,(*Q).y);
    (*Q).isInfinity = P.isInfinity;
}
*/

// Entrer le point dans le domaine de Montgomery
void transfMongPointFp2(PointFp2 *P){
    transfMongPol((*P).x,2);
    transfMongPol((*P).y,2);
    transfMongPol((*P).z,2);
}

// Entrer le point dans le domaine de Montgomery
void transfMongPointFp (PointFp *P){
	Montgomery((*P).x,R2,(*P).x);
    Montgomery((*P).y,R2,(*P).y);
}

void invTransMongPointFp2(PointFp2 P, PointFp2 *Q){
    invTransMongPol(P.x,(*Q).x,2);
    invTransMongPol(P.y,(*Q).y,2);
    invTransMongPol(P.z,(*Q).z,2);
}
/*
void afficherPointFp2 (PointFp2 P){
    PRINTHex2D(P.x,2);
    PRINTHex2D(P.y,2);
    PRINTHex2D(P.z,2);
}
*/

void invTransMongPointFp(PointFp P, PointFp *Q){
	Montgomery(P.x,UN,(*Q).x);
	Montgomery(P.y,UN,(*Q).y);
}


int isInfinityFp2(PointFp2 P){
    int i,j;
    for(i=0;i<2;i++)
        for(j=0;j<8;j++) if(P.z[i][j]!=0) return 0;
    return 1;
}
