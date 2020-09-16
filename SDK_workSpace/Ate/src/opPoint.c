#include "headers.h"

// Affectation
void affPointFp2(PointFp2 P, PointFp2 *Q){
    affectFp2(P.x,(*Q).x);
    affectFp2(P.y,(*Q).y);
    affectFp2(P.z,(*Q).z);
}

// Frobenius d'un point Fp2
void frobeniuspFp2 (PointFp2 Q, PointFp2 *frob){
    conjugFp2(Q.x,(*frob).x);
    conjugFp2(Q.y,(*frob).y);
    conjugFp2(Q.z,(*frob).z);
}

// Opposé d'un point
void oppPointFp2 (PointFp2 P, PointFp2 *Q){
    affectFp2(P.x,(*Q).x);
    oppFp2(P.y,(*Q).y);
    affectFp2(P.z,(*Q).z);
}

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

/*
void affPointFp2(PointFp2 P, PointFp2 *Q){
    affectFp2(P.x,(*Q).x);
    affectFp2(P.y,(*Q).y);
    affectFp2(P.z,(*Q).z);
}

void oppPointFp2 (PointFp2 P, PointFp2 *Q){
    affectFp2(P.x,(*Q).x);
    oppFp2(P.y,(*Q).y);
    affectFp2(P.z,(*Q).z);
}

void frobeniuspFp2 (PointFp2 Q, PointFp2 *frob){
    conjugFp2(Q.x,(*frob).x);
    conjugFp2(Q.y,(*frob).y);
    conjugFp2(Q.z,(*frob).z);
}



void transfMongPointFp2(PointFp2 *P){
    transfMongPol((*P).x,2);
    transfMongPol((*P).y,2);
    transfMongPol((*P).z,2);
}

void invTransMongPointFp2(PointFp2 P, PointFp2 *Q){
    invTransMongPol(P.x,(*Q).x,2);
    invTransMongPol(P.y,(*Q).y,2);
    invTransMongPol(P.z,(*Q).z,2);
}

void afficherPointFp2 (PointFp2 P){
    PRINTHex2D(P.x,2);
    PRINTHex2D(P.y,2);
    PRINTHex2D(P.z,2);
}

void transfMongPointFp (PointFp *P){
    montgomery((*P).x,R2,p,m,(*P).x);
    montgomery((*P).y,R2,p,m,(*P).y);
}

void invTransMongPointFp(PointFp P, PointFp *Q){
    montgomery(P.x,UN,p,m,(*Q).x);
    montgomery(P.y,UN,p,m,(*Q).y);
}

void afficherPointFp (PointFp P){
    PRINTHex(P.x);
    PRINTHex(P.y);
}

int isInfinity(PointFp2 P){
    int i,j;
    for(i=0;i<2;i++)
        for(j=0;j<8;j++) if(P.z[i][j]!=0) return 0;
    return 1;
}

void toAffineFp2(PointFp P, PointFp2 *Q){
    setIN(P.x,(*Q).x[0]);
    initNul((*Q).x[1]);
    setIN(P.y,(*Q).y[0]);
    initNul((*Q).y[1]);
    setIN(R,(*Q).z[0]);
    initNul((*Q).z[1]);
}

void toAffineFp (PointFp2 P, PointFp *Q){
    setIN(P.x[0],(*Q).x);
    setIN(P.y[0],(*Q).y);
}

int equalPointFp2 (PointFp2 P, PointFp2 Q){
    return (equalsFp2(P.x,Q.x) &&
            equalsFp2(P.y,Q.y) &&
            equalsFp2(P.z,Q.z));
}

int areOpp (PointFp2 P1, PointFp2 P2){
    unsigned long oy2[2][9];
    oppFp2(P2.y,oy2);
    return (equalsFp2(P1.x, P2.x) && equalsFp2(P1.y, oy2));
}

int addAfineFp2 (PointFp2 P1, PointFp2 P2, PointFp2 *T, unsigned long lambda[2][9]){
    if (isInfinity(P1)) {
        affPointFp2(P2, T);
    }
    else if (isInfinity(P2)){
        affPointFp2(P1, T);
    }
    else if(areOpp(P1,P2)){
        setIN(R,(*T).x[0]); initNul((*T).x[1]);
        setIN(R,(*T).y[0]); initNul((*T).y[1]);
        setIN(R,(*T).z[0]); initNul((*T).z[1]);
        printf("infini");
    }else{
        unsigned long lam[2][9],P1x2[2][9],denom[2][9];

        if(equalPointFp2(P1,P2)){
            squarFp2(P1.x,P1x2);
            addFp2(P1x2,P1x2,lam); addFp2(lam,P1x2,lam);

            addFp2(P1.y,P1.y,denom);
            invFp2(denom,denom);

            karatsubaFp2(lam,denom,lam);
        }else{
            subFp2(P2.y,P1.y,lam);

            subFp2(P2.x,P1.x,denom);
            invFp2(denom,denom);

            karatsubaFp2(lam,denom,lam);
        }

        squarFp2(lam,(*T).x);
        subFp2((*T).x,P1.x,(*T).x);
        subFp2((*T).x,P2.x,(*T).x);

        subFp2(P1.x,(*T).x,(*T).y);
        karatsubaFp2((*T).y,lam,(*T).y);
        subFp2((*T).y,P1.y,(*T).y);

        setIN(R,(*T).z[0]); initNul((*T).z[1]);

        if(lambda!=NULL) affectFp2(lam,lambda);
    }
}

void mulPointFp2 (PointFp2 P, unsigned long a[], unsigned long L,PointFp2 *T){
    int i,j,lastBit[9];
    indLastBit(a,L,lastBit);
    PointFp2 R;
    affPointFp2(P,&R);
    for(j=lastBit[1]-1;j>=0;j--){
        addAfineFp2(R,R,&R,NULL);
        if(getBitIndex(a[lastBit[0]],j)==1) addAfineFp2(R,P,&R,NULL);
    }
    for(i=lastBit[0]-1;i>=0;i--){
        for(j=31;j>=0;j--){

            addAfineFp2(R,R,&R,NULL);
            if(getBitIndex(a[i],j)==1) addAfineFp2(R,P,&R,NULL);
        }
    }
    affPointFp2(R,T);
}

void mulPointFp (PointFp Q, unsigned long a[], unsigned long L,PointFp *T){
    PointFp2 P,R;
    toAffineFp2(Q,&P);
    mulPointFp2(P,a,L,&R);
    toAffineFp(R,T);
}

int indLastBit (unsigned long a[], unsigned long L, unsigned long lastBit[2]){
    int i,j;
    for(i=L-1;i>=0;i--){
            for(j=31;j>=0;j--){
            if(getBitIndex(a[i],j)==1) goto finish;
        }
    }
    finish:
    lastBit[0]=i; lastBit[1]=j;
    return(i*32+j);
}
*/
